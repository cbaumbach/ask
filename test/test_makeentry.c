#include "unity_fixture.h"
#include "makeentry.h"

TEST_GROUP(makeentry);

TEST_SETUP(makeentry)
{
}

TEST_TEAR_DOWN(makeentry)
{
}

TEST(makeentry, init)
{
    const char *left = "left";
    const char *right = "right";
    Entry e;

    e = makeentry(left, right);
    TEST_ASSERT_EQUAL_INT(0, e.passed);
    TEST_ASSERT_EQUAL_STRING("left", e.left);
    TEST_ASSERT_EQUAL_STRING("right", e.right);
}
