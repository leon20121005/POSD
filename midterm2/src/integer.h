#ifndef INTEGER_H
#define INTEGER_H

#include "element.h"

class Integer: public Element
{
    public:
        Integer(int integer):_integer(integer)
        {
        }

        std::string toString() const
        {
            return std::to_string(_integer);
        }
    private:
        int _integer;
};

#endif
