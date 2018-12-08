#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include "find_flattened_set_visitor.h"
#include "element_iterator.h"

class Element
{
    public:
        void add(Element* element)
        {
            throw std::string("unable to add");
        }

        virtual std::string toString() = 0;
        virtual void accept(FindFlattenedSetVisitor* visitor) = 0;

        virtual ElementIterator* createIterator()
        {
            return nullptr;
        }
    private:
};

#endif
