#include "find_node_by_pathname_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"
#include <iostream>

FindNodeByPathnameVisitor::FindNodeByPathnameVisitor(std::vector<std::string>* pathnames):_pathnames(pathnames)
{
}

void FindNodeByPathnameVisitor::visitFile(File* file)
{
    for (std::vector<std::string>::iterator iter = _pathnames->begin(); iter != _pathnames->end(); iter++)
    {
        if (file->name() == *iter)
        {
            _nodes.push_back(file);
        }
    }
}

void FindNodeByPathnameVisitor::visitFolder(Folder* folder)
{
    if (_isFirstNode)
    {
        _isFirstNode = false;
    }
    else
    {
        for (std::vector<std::string>::iterator iter = _pathnames->begin(); iter != _pathnames->end(); iter++)
        {
            if (folder->name() == *iter)
            {
                _nodes.push_back(folder);
            }
        }
    }
    NodeIterator* nodeIterator = folder->createIterator();
    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->acceptChild(this);
    }
}

void FindNodeByPathnameVisitor::visitLink(Link* link)
{
    for (std::vector<std::string>::iterator iter = _pathnames->begin(); iter != _pathnames->end(); iter++)
    {
        if (link->name() == *iter)
        {
            _nodes.push_back(link);
        }
    }
    if (link->getSource() != nullptr)
    {
        link->getSource()->acceptChild(this);
    }
}

// return the Node object if the path indicate the node in the file system, and if not, return nullptr.
Node* FindNodeByPathnameVisitor::getNode() const
{
    if (_nodes.size() == 0)
    {
        return nullptr;
    }
    else
    {
        return _nodes[0];
    }
}

void FindNodeByPathnameVisitor::clearResult()
{
    _nodes.clear();
    _isFirstNode = true;
}

std::string FindNodeByPathnameVisitor::findResult()
{
    return "";
}
