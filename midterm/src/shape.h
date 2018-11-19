#ifndef SHAPE_H
#define SHAPE_H

#include "find_area_visitor.h"

class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;

        virtual Shape* getChild(int index)
        {
            return this;
        }

        virtual int numberOfChild()
        {
            return 0;
        }

        void accept(FindAreaVisitor* findAreaVisitor)
        {
            findAreaVisitor->visit(this);
        }

        void acceptChild(FindAreaVisitor* findAreaVisitor)
        {
            findAreaVisitor->visitChild(this);
        }
};

#endif
