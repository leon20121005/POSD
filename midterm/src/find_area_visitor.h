#ifndef FIND_AREA_VISITOR_H
#define FIND_AREA_VISITOR_H

#include <vector>

class Shape;

class FindAreaVisitor
{
    public:
        FindAreaVisitor(double min, double max);
        void visit(Shape* shape);
        void visitChild(Shape* shape);
        std::vector<Shape*> findResult();
    private:
        double _min;
        double _max;
        std::vector<Shape*> _result;
};

#endif
