#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <wx/button.h>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "observer.h"
#include "node_model.h"
#include "node_iterator.h"

enum
{
    wxID_BUTTON = wxID_HIGHEST + 1
};

class TreeFrame: public wxFrame, public Observer
{
    public:
        TreeFrame(const wxChar* title, int xPosition, int yPosition, int width, int height, std::string rootPath):wxFrame((wxFrame*)nullptr, -1, title, wxPoint(xPosition, yPosition), wxSize(width, height))
        {
            _treeCtrl = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(200, 400), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS);

            _nodeModel = new NodeModel(rootPath);
            _nodeModel->attach(this);
            this->initialize();

            _textCtrl = new wxTextCtrl(this, -1, wxString("Welcome to POSD_EDITOR"), wxPoint(200, 0), wxSize(400, 350), wxTE_MULTILINE);
            _button = new wxButton(this, wxID_BUTTON, wxString("Save"), wxPoint(200, 350), wxSize(400, 50));
        }

        void onClick(wxTreeEvent& event)
        {
            wxTreeItemId nodeId = event.GetItem();
            _currentOpenPath = appendPath(nodeId);
            std::cout << "File " << _currentOpenPath << " clicked" << std::endl;
            // std::cout << readFile(path) << std::endl;

            struct stat st;
            if (lstat(_currentOpenPath.c_str(), &st) == 0)
            {
                if (S_ISREG(st.st_mode))
                {
                    std::string fileType = Node::split(_currentOpenPath, ".")[1];
                    std::cout << "Type: file (" << fileType << ")" << std::endl;
                    // 二進位檔
                    if (fileType == "out")
                    {
                        _textCtrl->SetValue(wxString("This file is not displayes in the editor because it uses an unsupported text encoding"));
                        _button->Enable(false);
                    }
                    else
                    {
                        _textCtrl->LoadFile(wxString(_currentOpenPath));
                        _button->Enable(true);
                    }
                }
                else if (S_ISLNK(st.st_mode))
                {
                    std::cout << "Type: link" << std::endl;
                    _textCtrl->SetValue(wxString("This is a link"));
                    _button->Enable(false);
                }
                else if (S_ISDIR(st.st_mode))
                {
                    std::cout << "Type: directory" << std::endl;
                    _textCtrl->SetValue(wxString("This is a directory"));
                    _button->Enable(false);
                }
            }
        }

        void onEdit(wxTreeEvent& event)
        {
            wxTreeItemId oldNodeId = event.GetItem();
            std::string oldNodeName = _treeCtrl->GetItemText(oldNodeId).ToStdString();
            std::string newNodeName = event.GetLabel().ToStdString();
            // 如果沒有變動則直接return
            if (newNodeName == "")
            {
                return;
            }
            std::string message = "label edited: " + newNodeName + " -- old name was " + oldNodeName;
            wxMessageDialog* messageDialog = new wxMessageDialog(this, wxString(message), wxString("Confirm"), wxYES_NO | wxCANCEL);
            if (messageDialog->ShowModal() == wxID_YES)
            {
                if (renameFile(oldNodeId, newNodeName) == 0)
                {
                    std::cout << "Node " << oldNodeName << " edited to " << newNodeName << std::endl;
                }
                else
                {
                    std::cout << "Error node " << oldNodeName << " edited to " << newNodeName << std::endl;
                }
            }
            else
            {
                event.Veto();
                std::cout << "Node " << oldNodeName << " edit canceled" << std::endl;
            }
        }

        void onSave(wxCommandEvent& event)
        {
            wxMessageDialog* messageDialog = new wxMessageDialog(this, wxString("You want save?"), wxString("Confirm"), wxYES_NO | wxCANCEL);
            if (messageDialog->ShowModal() == wxID_YES)
            {
                _textCtrl->SaveFile(wxString(_currentOpenPath));
                _nodeModel->refresh();
                std::cout << "File " << _currentOpenPath << " saved" << std::endl;
            }
        }

        void update()
        {
            _treeCtrl->DeleteAllItems();
            this->initialize();
            std::cout << "wxTreeCtrl updated" << std::endl;
        }
    private:
        // 初始化樹
        void initialize()
        {
            _root = _nodeModel->getRootNode();
            wxTreeItemId rootId = _treeCtrl->AddRoot(wxString(_root->name() + ", " + std::to_string(_root->size())));
            NodeIterator* nodeIterator = _root->createIterator();
            for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
            {
                appendItem(rootId, nodeIterator->currentItem());
            }
            _treeCtrl->ExpandAllChildren(rootId);
        }

        // 遞迴串接樹
        void appendItem(wxTreeItemId parentId, Node* node)
        {
            wxTreeItemId nodeId = _treeCtrl->AppendItem(parentId, wxString(node->name() + ", " + std::to_string(node->size())));
            NodeIterator* nodeIterator = node->createIterator();
            for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
            {
                appendItem(nodeId, nodeIterator->currentItem());
            }
        }

        // 遞迴串接檔案路徑(string)
        std::string appendPath(wxTreeItemId nodeId)
        {
            std::string path = "";
            path += Node::split(_treeCtrl->GetItemText(nodeId).ToStdString(), ",")[0];
            if (_treeCtrl->GetItemParent(nodeId) != nullptr)
            {
                path = appendPath(_treeCtrl->GetItemParent(nodeId)) + "/" + path;
            }
            return path;
        }

        // 遞迴串接檔案路徑(vector)
        std::vector<std::string>* appendPathVector(wxTreeItemId nodeId, std::vector<std::string>* path = new std::vector<std::string>())
        {
            path->insert(path->begin(), Node::split(_treeCtrl->GetItemText(nodeId).ToStdString(), ",")[0]);
            if (_treeCtrl->GetItemParent(nodeId) != nullptr)
            {
                appendPathVector(_treeCtrl->GetItemParent(nodeId), path);
            }
            return path;
        }

        std::string readFile(std::string path)
        {
            std::string line = "";
            std::ifstream inputFileStream(path);
            if (inputFileStream.is_open())
            {
                while (std::getline(inputFileStream, line))
                {
                    std::cout << line << "\n";
                }
                inputFileStream.close();
            }
            return line;
        }

        // 修改檔名
        int renameFile(wxTreeItemId oldNodeId, std::string newNodeName)
        {
            std::string oldNodePath = appendPath(oldNodeId);
            std::string newNodePath = "";
            std::vector<std::string> splitResult = Node::split(oldNodePath, "/");
            for (std::vector<std::string>::iterator iter = splitResult.begin(); iter != splitResult.end() - 1; iter++)
            {
                newNodePath += *iter + "/";
            }
            newNodePath += Node::split(newNodeName, ",")[0];
            return rename(oldNodePath.c_str(), newNodePath.c_str());
        }

        wxTreeCtrl *_treeCtrl;
        wxTextCtrl* _textCtrl;
        wxButton* _button;
        NodeModel* _nodeModel;
        Node* _root;
        std::string _currentOpenPath;
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
// 設定事件的handler函式
EVT_TREE_ITEM_ACTIVATED(wxID_ANY, TreeFrame::onClick)
EVT_TREE_END_LABEL_EDIT(wxID_ANY, TreeFrame::onEdit)
EVT_BUTTON(wxID_BUTTON, TreeFrame::onSave)
END_EVENT_TABLE()

#endif
