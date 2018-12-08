#include "element_iterator.h"

class NullIterator: public ElementIterator
{
    public:
        void first()
        {
        }

        Element* currentItem()
        {
            return nullptr;
        }

        void next()
        {
        }

        bool isDone()
        {
            return true;
        }
};
