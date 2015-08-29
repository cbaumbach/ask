#include "unity_fixture.h"
#include "prompt.h"
#include "makeentry.h"

TEST_GROUP(prompt);

TEST_SETUP(prompt)
{
}

TEST_TEAR_DOWN(prompt)
{
}

TEST(prompt, left)
{
    const char *s;
    Entry e = makeentry("left", "right");

    s = prompt(e, LEFT);

    TEST_ASSERT_EQUAL_STRING("left", s);
}

TEST(prompt, right)
{
    const char *s;
    Entry e = makeentry("left", "right");

    s = prompt(e, RIGHT);

    TEST_ASSERT_EQUAL_STRING("right", s);
}
