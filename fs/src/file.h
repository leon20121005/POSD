#include "node.h"

class File: public Node
{
    public:
        File(const char* path):Node(path)
        {
        }

        string find(string nodeName)
        {
            vector<string>* splitResult = split(nodeName, "/");
            if ((*splitResult)[splitResult->size() - 1] == this->name())
            {
                return nodeName;
            }
        }
};
