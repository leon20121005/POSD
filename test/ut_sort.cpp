#include <iostream>
#include "gtest/gtest.h"

#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"

#include <vector>
#include "../src/sort.h"

using namespace std;

TEST(SortTest, first)
{
    ASSERT_TRUE(true);
}

TEST(SortTest, sortByArea)
{
    vector<Shape*>* shapeList = new vector<Shape*>();
    shapeList->push_back(new Circle(5.0));
    shapeList->push_back(new Rectangle(4.0, 5.0));
    shapeList->push_back(new Triangle(3.0, 0.0, 0.0, 0.0, 0.0, 4.0));

    Sort* sort = new Sort(shapeList);

    sort->sortArea([](Shape* a, Shape* b)
    {
        return a->area() > b->area();
    });
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->area() << endl;
    }
    ASSERT_NEAR(78.5398, (*shapeList)[0]->area(), 0.0001);

    sort->sortArea([](Shape* a, Shape* b)
    {
        return a->area() < b->area();
    });
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->area() << endl;
    }
    ASSERT_NEAR(6, (*shapeList)[0]->area(), 0.1);
}

TEST(SortTest, sortByPerimeter)
{
    vector<Shape*>* shapeList = new vector<Shape*>();
    shapeList->push_back(new Circle(5.0));
    shapeList->push_back(new Rectangle(4.0, 5.0));
    shapeList->push_back(new Triangle(3.0, 0.0, 0.0, 0.0, 0.0, 4.0));

    Sort* sort = new Sort(shapeList);

    sort->sortPerimeter(perimeterDescendingComparison);
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->perimeter() << endl;
    }
    ASSERT_NEAR(31.4159, (*shapeList)[0]->perimeter(), 0.0001);

    sort->sortPerimeter(perimeterAscendingComparison);
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->perimeter() << endl;
    }
    ASSERT_NEAR(12, (*shapeList)[0]->perimeter(), 0.1);
}

TEST(SortTest, sortByCompactness)
{
    vector<Shape*>* shapeList = new vector<Shape*>();
    shapeList->push_back(new Circle(5.0));
    shapeList->push_back(new Rectangle(4.0, 5.0));
    shapeList->push_back(new Triangle(3.0, 0.0, 0.0, 0.0, 0.0, 4.0));

    Sort* sort = new Sort(shapeList);

    sort->sortCompactness(CompactnessDescendingComparison());
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->compactness() << endl;
    }
    ASSERT_NEAR(24, (*shapeList)[0]->compactness(), 0.1);

    sort->sortCompactness(CompactnessAscendingComparison());
    for (int index = 0; index < shapeList->size(); index++)
    {
        cout << (*shapeList)[index]->compactness() << endl;
    }
    ASSERT_NEAR(12.5664, (*shapeList)[0]->compactness(), 0.0001);
}
