#ifndef SET_H
#define SET_H

#include "element.h"
#include <vector>

class Set: public Element
{
    public:
        class SetIterator: public ElementIterator
        {
            public:
                SetIterator(Set* set):_set(set)
                {
                }

                void first()
                {
                    _iter = _set->_elements.begin();
                }

                Element* currentItem()
                {
                    if (this->isDone())
                    {
                        throw std::string("no current item");
                    }
                    return *_iter;
                }

                void next()
                {
                    if (this->isDone())
                    {
                        throw std::string("moving past the end");
                    }
                    _iter++;
                }

                bool isDone()
                {
                    return _iter == _set->_elements.end();
                }
            private:
                Set* _set;
                std::vector<Element*>::iterator _iter;
        };

        Set()
        {
        }

        void add(Element* element)
        {
            _elements.push_back(element);
        }

        std::string toString()
        {
            ElementIterator* iterator = this->createIterator();
            std::string result = "{";
            bool isFirst = true;
            for (iterator->first(); !iterator->isDone(); iterator->next())
            {
                if (isFirst)
                {
                    result += iterator->currentItem()->toString();
                    isFirst = false;
                }
                else
                {
                    result += "," + iterator->currentItem()->toString();
                }
            }
            result += "}";
            return result;
        }

        void accept(FindFlattenedSetVisitor* visitor)
        {
            visitor->visitSet(this);
        }

        ElementIterator* createIterator()
        {
            return new SetIterator(this);
        }
    private:
        std::vector<Element*> _elements;
};

#endif
