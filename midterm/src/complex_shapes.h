#ifndef COMPLEX_SHAPES_H
#define COMPLEX_SHAPES_H

#include <vector>
#include "shape.h"

class ComplexShapes: public Shape
{
    public:
        ComplexShapes(std::vector<Shape*>* shapes)
        {
            _shapes = shapes;
        }

        void add(Shape* shape);
        double area() const;
        double perimeter() const;
        Shape* getChild(int index);
        int numberOfChild();
    private:
        std::vector<Shape*>* _shapes;
};

#endif
