#include "complex_shapes.h"

void ComplexShapes::add(Shape* shape)
{
    _shapes->push_back(shape);
}

double ComplexShapes::area() const
{
    double sum;
    for (int index = 0; index < _shapes->size(); index++)
    {
        sum += (*_shapes)[index]->area();
    }
    return sum;
}

double ComplexShapes::perimeter() const
{
    double sum;
    for (int index = 0; index < _shapes->size(); index++)
    {
        sum += (*_shapes)[index]->perimeter();
    }
    return sum;
}

Shape* ComplexShapes::getChild(int index)
{
    return (*_shapes)[index];
}

int ComplexShapes::numberOfChild()
{
    return _shapes->size();
}
