#include <math.h>

class Circle
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
