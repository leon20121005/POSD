#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
    public:
        Triangle(double a, double b, double c):_a(a),_b(b),_c(c)
        {
            if (!(this->isTriangle()))
            {
                throw std::string("illegal triangle");
            }
        }

        bool isTriangle() const
        {
            if (_a > 0 && _b > 0 && _c > 0 && _a + _b > _c && _b + _c > _a && _a + _c > _b)
            {
                return true;
            }
            return false;
        }
    private:
        double _a;
        double _b;
        double _c;
};

#endif
