#include <iostream>
#include "gtest/gtest.h"

#include "../src/triangle.h"

using namespace std;

TEST(ShapeTest, createNormalTriangle)
{
    Triangle* triangle = new Triangle(2.0, 1.0, 8.0, 2.0, 12.0, 9.0);
}

TEST(ShapeTest, createIllegalTriangle)
{
    try
    {
        Triangle* triangle = new Triangle(1.0, 0.0, 2.0, 0.0, 3.0, 0.0);
        ASSERT_TRUE(false);
    }
    catch (string exception)
    {
        ASSERT_EQ(std::string("illegal triangle"), exception);
    }
}
