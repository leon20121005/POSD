#include "node.h"
#include "node_visitor.h"
#include <vector>

class FindLinkVisitor: public NodeVisitor
{
    public:
        FindLinkVisitor();
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        void visitLink(Link* link);
        std::vector<Node*> getLinks();
        void clearResult();
    private:
        std::vector<Node*> _links;
};
