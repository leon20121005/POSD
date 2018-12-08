#ifndef TRIANGLE_FACTORY_H
#define TRIANGLE_FACTORY_H

#include "triangle.h"
#include <string>

class TriangleFactory
{
    public:
        TriangleFactory()
        {
        }

        Triangle* create(int a, int b, int c)
        {
            try
            {
                return new Triangle(a, b, c);
            }
            catch (std::string exception)
            {
                return nullptr;
            }
        }
    private:
};

#endif
