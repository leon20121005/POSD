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
            if (splitResult->size() > 1 && (*splitResult)[splitResult->size() - 1] == this->name())
            {
                result += nodeName;
            }
            for (int index = 0; index < _children.size(); index++)
            {
                string next = _children[index]->find(newNodeName);
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
    private:
        vector<Node*> _children;
};
