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

TEST(SortTest, Sorting)
{
    vector<Shape*>* shapeList = new vector<Shape*>();
    shapeList->push_back(new Circle(5.0));
    shapeList->push_back(new Rectangle(4.0, 5.0));
    shapeList->push_back(new Triangle(3.0, 0.0, 0.0, 0.0, 0.0, 4.0));

    Sort* sort = new Sort(shapeList);
    sort->sortPerimeter(perimeterDescendingComparison);

    cout << (*shapeList)[0]->perimeter() << endl;
    cout << (*shapeList)[1]->perimeter() << endl;
    cout << (*shapeList)[2]->perimeter() << endl;

    sort->sortCompactness(CompactnessAscendingComparison());

    cout << (*shapeList)[0]->compactness() << endl;
    cout << (*shapeList)[1]->compactness() << endl;
    cout << (*shapeList)[2]->compactness() << endl;
}
