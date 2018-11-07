#include "node_visitor.h"

class FindVisitor: public NodeVisitor
{
    public:
        FindVisitor(std::string name);
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        std::string findResult();
    private:
        std::string _name;
        std::string _result;
};
