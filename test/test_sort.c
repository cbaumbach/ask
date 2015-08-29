#include "unity_fixture.h"
#include "sort.h"

TEST_GROUP(sort);

TEST_SETUP(sort)
{
}

TEST_TEAR_DOWN(sort)
{
}

TEST(sort, by_left)
{
    Entry e1 = makeentry("abcd", "ignore");
    Entry e2 = makeentry("efgh", "ignore");
    int i;

    i = by_left(&e1, &e2);
    TEST_ASSERT_TRUE(i < 0);

    i = by_left(&e1, &e1);
    TEST_ASSERT_EQUAL_INT(0, i);

    i = by_left(&e2, &e1);
    TEST_ASSERT_TRUE(i > 0);
}

TEST(sort, by_right)
{
    Entry e1 = makeentry("ignore", "abcd");
    Entry e2 = makeentry("ignore", "efgh");
    int i;

    i = by_right(&e1, &e2);
    TEST_ASSERT_TRUE(i < 0);

    i = by_right(&e1, &e1);
    TEST_ASSERT_EQUAL_INT(0, i);

    i = by_right(&e2, &e1);
    TEST_ASSERT_TRUE(i > 0);
}
