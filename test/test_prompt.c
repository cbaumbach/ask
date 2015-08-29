#include "unity_fixture.h"
#include "prompt.h"
#include "from.h"
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

TEST(prompt, compare_with_left)
{
    const char *answer = "left";
    Entry e = makeentry("left", "right");
    int i;

    i = correct(answer, e, RIGHT);

    TEST_ASSERT_EQUAL_INT(1, i);
}

TEST(prompt, compare_with_right)
{
    const char *answer = "right";
    Entry e = makeentry("left", "right");
    int i;

    i = correct(answer, e, LEFT);

    TEST_ASSERT_EQUAL_INT(1, i);
}

TEST(prompt, fail_with_left)
{
    const char *answer = "wrong";
    Entry e = makeentry("left", "right");
    int i;

    i = correct(answer, e, RIGHT);

    TEST_ASSERT_EQUAL_INT(0, i);
}

TEST(prompt, fail_with_right)
{
    const char *answer = "wrong";
    Entry e = makeentry("left", "right");
    int i;

    i = correct(answer, e, LEFT);

    TEST_ASSERT_EQUAL_INT(0, i);
}
