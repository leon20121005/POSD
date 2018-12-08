#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
    public:
        void add(Element* element)
        {
            throw std::string("unable to add");
        }

        virtual std::string toString() const = 0;
    private:
};

#endif
