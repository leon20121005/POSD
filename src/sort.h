#ifndef SORT_H
#define SORT_H

#include <algorithm>

using namespace std;

class Sort
{
    public:
        Sort(vector<Shape*>* shapeList):_shapeList(shapeList)
        {
        }

        // The argument ** Accept comparison ** can accept lambda, function, and object
        template<typename Compare>
        void sortArea(Compare compare)
        {
            sort(_shapeList->begin(), _shapeList->end(), compare);
        }

        template<typename Compare>
        void sortPerimeter(Compare compare)
        {
            for (vector<Shape*>::iterator i = _shapeList->begin() + 1; i != _shapeList->end(); ++i)
            {
                for (vector<Shape*>::iterator j = i; j != _shapeList->begin(); --j)
                {
                    if (!compare(*(j - 1), *j))
                    {
                        iter_swap(j - 1, j);
                    }
                }
            }
        }

        template<class Compare>
        void sortCompactness(Compare compare)
        {
            sort(_shapeList->begin(), _shapeList->end(), compare);
        }
    private:
        vector<Shape*>* _shapeList;
};

// You should implement area ascending and descending lambda function as parameter for Sort::sortArea()

// You should use those functions as parameter for Sort::sortPerimeter()
bool perimeterDescendingComparison(Shape *a, Shape *b)
{
    return a->perimeter() > b->perimeter();
}

bool perimeterAscendingComparison(Shape *a, Shape *b)
{
    return a->perimeter() < b->perimeter();
}

// You should use those objects as parameter for Sort::sortCompactness()
class CompactnessDescendingComparison
{
    public:
        bool operator() (Shape* a, Shape* b)
        {
            return a->compactness() > b->compactness();
        }
};

class CompactnessAscendingComparison
{
    public:
        bool operator() (Shape* a, Shape* b)
        {
            return a->compactness() < b->compactness();
        }
};

#endif
