#ifndef INTEGER_H
#define INTEGER_H

#include "element.h"
#include "null_iterator.h"

class Integer: public Element
{
    public:
        Integer(int integer):_integer(integer)
        {
        }

        std::string toString()
        {
            return std::to_string(_integer);
        }

        void accept(FindFlattenedSetVisitor* visitor)
        {
            visitor->visitInteger(this);
        }

        ElementIterator* createIterator()
        {
            return new NullIterator();
        }
    private:
        int _integer;
};

#endif
