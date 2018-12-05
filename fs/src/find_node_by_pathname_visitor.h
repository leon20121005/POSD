#include "node.h"
#include "node_visitor.h"
#include <vector>

class FindNodeByPathnameVisitor: public NodeVisitor
{
    public:
        FindNodeByPathnameVisitor(std::vector<std::string>* pathnames);
        void visitFolder(Folder* folder);
        void visitFile(File* file);
        void visitLink(Link* link);
        Node* getNode() const;
        void clearResult();
        std::string findResult();
    private:
        std::vector<std::string>* _pathnames;
        std::vector<Node*> _nodes;
        bool _isFirstNode;
};
