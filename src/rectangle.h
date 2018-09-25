#include "shape.h"

class Rectangle: public Shape
{
    public:
        Rectangle(double length, double width):_length(length),_width(width)
        {
        }

        double area() const
        {
            return _length * _width;
        }

        double perimeter() const
        {
            return 2 * (_length + _width);
        }
    private:
        double _length;
        double _width;
};
