#include "find_area_visitor.h"
#include "shape.h"

FindAreaVisitor::FindAreaVisitor(double min, double max):_min(min),_max(max)
{
    _result = std::vector<Shape*>();
}

void FindAreaVisitor::visit(Shape* shape)
{
    _result = std::vector<Shape*>(); // reset result
    for (int index = 0; index < shape->numberOfChild(); index++)
    {
        shape->getChild(index)->acceptChild(this);
    }
}

void FindAreaVisitor::visitChild(Shape* shape)
{
    if (shape->area() <= _max && shape->area() >= _min)
    {
        _result.push_back(shape);
    }
    for (int index = 0; index < shape->numberOfChild(); index++)
    {
        shape->getChild(index)->acceptChild(this);
    }
}

std::vector<Shape*> FindAreaVisitor::findResult()
{
    return _result;
}
