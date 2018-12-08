#ifndef FIND_FLATTENED_SET_VISITOR_H
#define FIND_FLATTENED_SET_VISITOR_H

#include <string>

class Integer;
class Set;

class FindFlattenedSetVisitor
{
    public:
        FindFlattenedSetVisitor();
        void visitInteger(Integer* integer);
        void visitSet(Set* set);
        std::string getResult();
    private:
        std::string _result;
};

#endif
