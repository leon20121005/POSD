#include <iostream>
#include "gtest/gtest.h"

#include "../src/integer.h"
#include "../src/set.h"
#include "../src/find_flattened_set_visitor.h"

using namespace std;

TEST(SetTest, createSingleIntegerSet)
{
    Integer* integer = new Integer(0);
    ASSERT_EQ("0", integer->toString());
}

TEST(SetTest, createComplexSet)
{
    Set* set = new Set();
    Set* set1 = new Set();
    set1->add(new Integer(2));
    Set* set2 = new Set();
    set2->add(new Integer(3));
    set2->add(new Integer(4));
    Set* set3 = new Set();
    set3->add(new Integer(5));
    set3->add(new Set());
    set2->add(set3);
    set->add(new Integer(1));
    set->add(set1);
    set->add(set2);
    ASSERT_EQ("{1,{2},{3,4,{5,{}}}}", set->toString());
}

TEST(SetTest, createFlattenedSet)
{
    Set* set = new Set();
    Set* set1 = new Set();
    set1->add(new Integer(2));
    Set* set2 = new Set();
    set2->add(new Integer(3));
    set2->add(new Integer(4));
    Set* set3 = new Set();
    set3->add(new Integer(5));
    set3->add(new Set());
    set2->add(set3);
    set->add(new Integer(1));
    set->add(set1);
    set->add(set2);

    FindFlattenedSetVisitor* visitor = new FindFlattenedSetVisitor();
    set->accept(visitor);
    ASSERT_EQ("1,2,3,4,5", visitor->getResult());
}
