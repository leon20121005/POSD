#ifndef SET_H
#define SET_H

#include "element.h"
#include <vector>

class Set: public Element
{
    public:
        Set()
        {
        }

        void add(Element* element)
        {
            _elements.push_back(element);
        }

        std::string toString() const
        {
            return "";
        }
    private:
        std::vector<Element*> _elements;
};

#endif
