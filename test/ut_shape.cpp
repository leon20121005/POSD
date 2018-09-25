#include <iostream>
#include "gtest/gtest.h"

#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"

using namespace std;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(ShapeTest, first)
{
    ASSERT_TRUE(true);
}

TEST(ShapeTest, Circle)
{
    Circle circle(10.0);
    ASSERT_NEAR(314.159, circle.area(), 0.001);
    ASSERT_NEAR(62.8318, circle.perimeter(), 0.0001);
}

TEST(ShapeTest, Rectangle)
{
    Rectangle rectangle(10.0, 5.0);
    ASSERT_NEAR(50.0, rectangle.area(), 0.1);
    ASSERT_NEAR(30.0, rectangle.perimeter(), 0.1);
}

TEST(ShapeTest, Triangle)
{
    Triangle triangle(2.0, 1.0, 8.0, 2.0, 12.0, 9.0);
    ASSERT_NEAR(19.0, triangle.area(), 0.1);
    ASSERT_NEAR(27.0, triangle.perimeter(), 0.1);
    ASSERT_TRUE(triangle.isTriangle());
}

TEST(ShapeTest, isTriangle)
{
    Triangle triangle(1.0, 0.0, 2.0, 0.0, 3.0, 0.0);
    ASSERT_ANY_THROW(triangle.isTriangle());    
}

TEST(ShapeTest, Sorting)
{
    Shape* shapeList[4] = {new Circle(5.0), new Rectangle(4.0, 5.0), new Triangle(3.0, 0.0, 0.0, 0.0, 0.0, 4.0)};
}
