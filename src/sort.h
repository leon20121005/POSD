class Sort
{
    public:
        Sort(std::vector<Shape*>* v):_v(v)
        {
        }

        // The argument ** Accept comparison ** can accept lambda, function, and object
        void sortArea(** Accept comparison **)
        {
        }

        void sortPerimeter(** Accept comparison **)
        {

        }

        void sortCompactness(** Accept comparison **)
        {

        }

    private:
        std::vector<Shape*>* _v;
};

// You should implement area ascending and descending lamda function as parameter for Sort::sortArea()

// You should use those functions as parameter for Sort::sortPerimeter()
bool perimeterDescendingComparison(Shape *a, Shape *b);

bool perimeterAscendingComparison(Shape *a, Shape *b);

// You should use those objects as parameter for Sort::sortCompactness()
class CompactnessAscendingComparison
{
};

class CompactnessDescendingComparison
{
};
