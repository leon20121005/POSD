#include "node.h"

class Folder: public Node
{
    public:
        friend class FindVisitor;

        Folder(const char* path):Node(path)
        {
        }

        void add(Node* node)
        {
            _children.insert(std::pair<std::string, Node*>(node->name(), node));
        }

        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitFolder(this);
        }
    private:
        std::map<std::string, Node*> _children;
};
