#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <cmath>

class Ellipse: public Shape
{
    public:
        Ellipse(double a, double b):_a(a),_b(b)
        {
        }

        double area() const
        {
            return M_PI * _a * _b;
        }

        double perimeter() const
        {
            return 2 * M_PI * sqrt((pow(_a, 2) + pow(_b, 2)) / 2);
        }
    private:
        double _a;
        double _b;
};

#endif
