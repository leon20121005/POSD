#include "find_flattened_set_visitor.h"
#include "integer.h"
#include "set.h"
#include "element_iterator.h"

#include <iostream>

FindFlattenedSetVisitor::FindFlattenedSetVisitor()
{
    _result = new Set();
}

void FindFlattenedSetVisitor::visitInteger(Integer* integer)
{
    // if (_result == "")
    // {
    //     _result += integer->toString();
    // }
    // else
    // {
    //     _result += "," + integer->toString();
    // }
    _result->add(integer);
}

void FindFlattenedSetVisitor::visitSet(Set* set)
{
    ElementIterator* iterator = set->createIterator();
    for (iterator->first(); !iterator->isDone(); iterator->next())
    {
        iterator->currentItem()->accept(this);
    }
}

// std::string FindFlattenedSetVisitor::getResult()
// {
//     return _result;
// }

Set* FindFlattenedSetVisitor::getResult()
{
    return _result;
}
