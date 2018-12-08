#ifndef ELEMENT_ITERATOR_H
#define ELEMENT_ITERATOR_H

class Element;

class ElementIterator
{
    public:
        virtual ~ElementIterator()
        {
        }
        virtual void first() = 0;
        virtual Element* currentItem() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
};

#endif
