#include <iostream>
#include "gtest/gtest.h"

#include "../src/triangle.h"
#include "../src/triangle_factory.h"

using namespace std;

TEST(ShapeTest, createNormalTriangle)
{
    Triangle* triangle = new Triangle(3, 4, 5);
    ASSERT_TRUE(true);
}

TEST(ShapeTest, createIllegalTriangle)
{
    try
    {
        Triangle* triangle = new Triangle(1, 1, 2);
        ASSERT_TRUE(false);
    }
    catch (string exception)
    {
        ASSERT_EQ(std::string("illegal triangle"), exception);
    }
}

TEST(ShapeTest, factoryCreateNormalTriangle)
{
    TriangleFactory* factory = new TriangleFactory();
    Triangle* triangle = factory->create(3, 4, 5);
    ASSERT_TRUE(true);
}

TEST(ShapeTest, factoryCreateIllegalTriangle)
{
    TriangleFactory* factory = new TriangleFactory();
    Triangle* triangle = factory->create(1, 1, 2);
    ASSERT_EQ(nullptr, triangle);
}
