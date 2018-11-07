#include "find_visitor.h"
#include "file.h"
#include "folder.h"

FindVisitor::FindVisitor(std::string name):_name(name)
{
}

void FindVisitor::visitFile(File* file)
{
    _result = file->find(_name);
}

void FindVisitor::visitFolder(Folder* folder)
{
    _result = folder->find(_name);
}

std::string FindVisitor::findResult()
{
    return _result;
}
