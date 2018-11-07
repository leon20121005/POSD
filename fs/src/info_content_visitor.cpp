#include "info_content_visitor.h"
#include "file.h"
#include "folder.h"
#include "node_iterator.h"

InfoContentVisitor::InfoContentVisitor()
{
}

void InfoContentVisitor::visitFile(File* file)
{
    _size += file->size();
}

void InfoContentVisitor::visitFolder(Folder* folder)
{
    NodeIterator* nodeIterator = folder->createIterator();
    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->accept(this);
    }
}

int InfoContentVisitor::getContentSize()
{
    return _size;
}
