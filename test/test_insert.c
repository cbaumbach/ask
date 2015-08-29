#include "unity_fixture.h"
#include "insert.h"
#include "makeentry.h"
#include <stdlib.h>

TEST_GROUP(insert);

TEST_SETUP(insert)
{
}

TEST_TEAR_DOWN(insert)
{
}

TEST(insert, maketab)
{
    Tab t = maketab();

    TEST_ASSERT_TRUE(t.e == NULL);
    TEST_ASSERT_EQUAL_INT(0, t.n);
    TEST_ASSERT_EQUAL_INT(0, t.size);
}

TEST(insert, empty_table)
{
    Tab t;
    Entry e;
    int i;

    e = makeentry("left", "right");
    t = maketab();
    i = insert(&t, e);

    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(1, t.n);
    TEST_ASSERT_TRUE(t.size >= t.n);
    TEST_ASSERT_EQUAL_STRING(e.left, t.e->left);
    TEST_ASSERT_EQUAL_STRING(e.right, t.e->right);
}
