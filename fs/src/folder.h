#include "node.h"

class Folder: public Node
{
    public:
        Folder(const char* path):Node(path)
        {
        }

        void add(Node* node)
        {
            _children.push_back(node);
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
            if ((*splitResult)[splitResult->size() - 1] == this->name())
            {
                return nodeName;
            }
            for (int index = 0; index < _children.size(); index++)
            {
                if (result != "")
                {
                    result += "\n" + _children[index]->find(newNodeName);
                }
                else
                {
                    result += _children[index]->find(newNodeName);
                }
            }
            return result;
        }
    private:
        vector<Node*> _children;
};
