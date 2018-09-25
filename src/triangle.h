#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <math.h>
#include "shape.h"

class Triangle: public Shape
{
    public:
        Triangle(double x1, double y1, double x2, double y2, double x3, double y3):_x1(x1),_y1(y1),_x2(x2),_y2(y2),_x3(x3),_y3(y3)
        {
            if (!(this->isTriangle()))
            {
                throw std::string("Not a triangle.");
            }
        }

        // 三角形面積 = (1 / 2) * 根號(AB向量長度平方 * AC向量長度平方 - (AB向量內積AC向量)平方)
        double area() const
        {
            double ab[2] = {_x2 - _x1, _y2 - _y1};
            double ac[2] = {_x3 - _x1, _y3 - _y1};
            return sqrt(pow(GetVectorLength(ab), 2) * pow(GetVectorLength(ac), 2) - pow(GetInnerProduct(ab, ac), 2)) / 2;
        }

        // 三角形周長 = AB向量長度 + AC向量長度 + BC向量長度
        double perimeter() const
        {
            double ab[2] = {_x2 - _x1, _y2 - _y1};
            double ac[2] = {_x3 - _x1, _y3 - _y1};
            double bc[2] = {_x3 - _x2, _y3 - _y2};
            return GetVectorLength(ab) + GetVectorLength(ac) + GetVectorLength(bc);
        }

        // 判斷是否為三角形：三個點是否在同一直線上，意即AB向量和AC向量的夾角是否為0度或180度
        bool isTriangle() const
        {
            double ab[2] = {_x2 - _x1, _y2 - _y1};
            double ac[2] = {_x3 - _x1, _y3 - _y1};
            if (abs(GetInnerProduct(ab, ac)) == GetVectorLength(ab) * GetVectorLength(ac))
            {
                return false;
            }
            return true;
        }
    private:
        // 計算內積
        double GetInnerProduct(double vector1[2], double vector2[2]) const
        {
            return vector1[0] * vector2[0] + vector1[1] * vector2[1];
        }

        // 計算向量長度
        double GetVectorLength(double vector[2]) const
        {
            return sqrt(pow(vector[0], 2) + pow(vector[1], 2));
        }

        double _x1;
        double _y1;
        double _x2;
        double _y2;
        double _x3;
        double _y3;
};

#endif
