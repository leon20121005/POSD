#ifndef CIRCLE_H
#define CIRCLE_H

#include <math.h>
#include "shape.h"

class Circle: public Shape
{
    public:
        Circle(double radius):_radius(radius)
        {
        }

        double area() const
        {
            return M_PI * _radius * _radius;
        }

        double perimeter() const
        {
            return 2 * M_PI * _radius;
        }
    private:
        double _radius;
};

#endif
