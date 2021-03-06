#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/ellipse.h"
#include "../src/rectangle.h"
#include "../src/circle.h"
#include "../src/complex_shapes.h"
#include "../src/find_area_visitor.h"
#include <vector>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
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
    ASSERT_NEAR(62.831, circle.perimeter(), 0.001);
}

TEST(ShapeTest, Rectangle)
{
    Rectangle rectangle(3, 4);
    ASSERT_NEAR(12, rectangle.area(), 0.001);
    ASSERT_NEAR(14, rectangle.perimeter(), 0.001);
}

TEST(ellipse, area)
{
    Ellipse ellipse(10, 5);
    ASSERT_NEAR(157, ellipse.area(), 0.1);
}

TEST(ellipse, perimeter)
{
    Shape* ellipse = new Ellipse(10, 5);
    ASSERT_NEAR(49.612, ellipse->perimeter(), 0.1);
}

TEST(ComplexShapes, Perimeter)
{
    Shape* ellipse = new Ellipse(1, 1);
    Shape* rectangle = new Rectangle(2, 4);
    std::vector<Shape*> shapes = {ellipse, rectangle};
    Shape* complexShapes = new ComplexShapes(&shapes);
    ASSERT_NEAR(18.28, complexShapes->perimeter(), 0.01);
}

TEST(ComplexShapes, Area)
{
    Shape* circle = new Circle(1);
    Shape* ellipse = new Ellipse(1, 1);
    Shape* rectangle = new Rectangle(2, 4);
    std::vector<Shape*> shapes = {circle, rectangle, ellipse};
    Shape* complexShapes = new ComplexShapes(&shapes);
    ASSERT_NEAR(14.28, complexShapes->area(), 0.01);
}

TEST(ComplexShapes, ChildOperation)
{
    Shape* circle = new Circle(1);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* ellipse = new Ellipse(1, 1);
    std::vector<Shape*> shapes = {};
    ComplexShapes* complexShapes = new ComplexShapes(&shapes);

    ASSERT_EQ(0, complexShapes->numberOfChild());
    complexShapes->add(circle);

    ASSERT_NEAR(3.14, complexShapes->getChild(0)->area(), 0.01);
    ASSERT_NEAR(6.28, complexShapes->getChild(0)->perimeter(), 0.01);
}

TEST(Visitor, FindAreaInLeaf)
{
    Shape* circle = new Circle(1);
    FindAreaVisitor* findAreaVisitor = new FindAreaVisitor(1, 5);

    circle->accept(findAreaVisitor);
    ASSERT_EQ(0, findAreaVisitor->findResult().size());
}

TEST(Visitor, FindAreaInComposite)
{
    Shape* circle = new Circle(1);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* ellipse = new Ellipse(1, 1);
    std::vector<Shape*> shapes = {circle, rectangle, ellipse};
    ComplexShapes* complexShapes = new ComplexShapes(&shapes);
    FindAreaVisitor* findAreaVisitor = new FindAreaVisitor(1, 5);

    complexShapes->accept(findAreaVisitor);
    ASSERT_EQ(2, findAreaVisitor->findResult().size());
}

TEST(Visitor,InitialAcceptWhenFunctionCall)
{
    Shape* circle = new Circle(1);
    Shape* circle2 = new Circle(2);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* ellipse = new Ellipse(1, 1);

    std::vector<Shape*> shapes = {circle, rectangle, circle2};
    ComplexShapes* complexShapes = new ComplexShapes(&shapes);
    std::vector<Shape*> shapes2 = {ellipse};
    ComplexShapes* complexShapes2 = new ComplexShapes(&shapes2);

    FindAreaVisitor* findAreaVisitor = new FindAreaVisitor(4, 15);

    complexShapes->accept(findAreaVisitor); // find 2
    complexShapes2->accept(findAreaVisitor); // find 0
    ASSERT_EQ(0, findAreaVisitor->findResult().size());
}

TEST(Visitor, FindAreaInNestedComposite)
{
    Shape* circle = new Circle(1);
    Shape* circle2 = new Circle(2);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* ellipse = new Ellipse(1, 1);

    std::vector<Shape*> shapes = {circle, rectangle, circle2};
    ComplexShapes* complexShapes2 = new ComplexShapes(&shapes);

    std::vector<Shape*> shapes2 = {ellipse, complexShapes2};
    ComplexShapes* complexShapes = new ComplexShapes(&shapes2);

    FindAreaVisitor* findAreaVisitor = new FindAreaVisitor(5, 24);

    complexShapes->accept(findAreaVisitor);
    ASSERT_EQ(3, findAreaVisitor->findResult().size());
}

TEST(Visitor, VisitDifferentComposite)
{
    Shape* circle = new Circle(1);
    Shape* circle2 = new Circle(2);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* ellipse = new Ellipse(1, 1);

    std::vector<Shape*> shapes = {circle, rectangle, circle2};
    ComplexShapes* complexShapes = new ComplexShapes(&shapes);
    std::vector<Shape*> shapes2 = {ellipse};
    ComplexShapes* complexShapes2 = new ComplexShapes(&shapes2);

    FindAreaVisitor* findAreaVisitor = new FindAreaVisitor(4, 8);

    complexShapes->accept(findAreaVisitor);
    ASSERT_EQ(1, findAreaVisitor->findResult().size());

    complexShapes2->accept(findAreaVisitor);
    ASSERT_EQ(0, findAreaVisitor->findResult().size());

    complexShapes2->add(complexShapes);
    complexShapes2->accept(findAreaVisitor);
    ASSERT_EQ(1, findAreaVisitor->findResult().size());
}
