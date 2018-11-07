#include "node.h"
#include "null_iterator.h"

class File: public Node
{
    public:
        File(const char* path):Node(path)
        {
        }

        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitFile(this);
        }

        NodeIterator* createIterator()
        {
            return new NullIterator();
        }
};
