#include "node.h"

class Folder: public Node
{
    public:
        Folder(const char* path):Node(path)
        {
        }

        void add(Node* node)
        {
            _children.insert(pair<string, Node*>(node->name(), node));
        }

        string find(string nodeName)
        {
            vector<string>* splitResult = split(nodeName, "/");
            string newNodeName;
            if (splitResult->size() == 1)
            {
                newNodeName = "./" + nodeName;
            }
            else
            {
                for (int index = 0; index < splitResult->size() - 1; index++)
                {
                    newNodeName += (*splitResult)[index] + "/";
                }
                newNodeName += this->name() + "/" + (*splitResult)[splitResult->size() - 1];
            }

            string result;
            if (splitResult->size() > 1 && (*splitResult)[splitResult->size() - 1] == this->name())
            {
                result += nodeName;
            }
            for (map<string, Node*>::iterator iter = _children.begin(); iter != _children.end(); iter++)
            {
                string next = iter->second->find(newNodeName);
                if (result != "" && next != "")
                {
                    result += "\n" + next;
                }
                else
                {
                    result += next;
                }
            }
            return result;
        }

        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitFolder(this);
        }
    private:
        map<string, Node*> _children;
};
