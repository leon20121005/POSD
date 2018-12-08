#include <iostream>
#include "gtest/gtest.h"

#include "../src/element.h"
#include "../src/integer.h"
#include "../src/set.h"

using namespace std;

TEST(SetTest, createNormalTriangle)
{
    Integer* integer = new Integer(0);
    ASSERT_EQ("0", integer->toString());
}
