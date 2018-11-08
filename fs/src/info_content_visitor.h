#include "node_visitor.h"

class InfoContentVisitor: public NodeVisitor
{
    public:
        InfoContentVisitor();
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        std::string findResult();
        void clearResult();
        int getContentSize();
    private:
        int _size;
};
