#include "node_visitor.h"

class InfoContentVisitor: public NodeVisitor
{
    public:
        InfoContentVisitor();
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        std::string findResult()
        {
            return "";
        }
        int getContentSize();
    private:
        int _size;
};
