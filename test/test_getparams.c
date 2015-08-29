#include "unity_fixture.h"
#include "getparams.h"
#include "from.h"
#include "err_msg.h"

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

TEST_GROUP(getparams);

TEST_SETUP(getparams)
{
}

TEST_TEAR_DOWN(getparams)
{
}

TEST(getparams, initparams)
{
    Params p = initparams();

    TEST_ASSERT_EQUAL_INT(LEFT, p.from);
    TEST_ASSERT_EQUAL_INT(ASIS, p.order);
    TEST_ASSERT_TRUE(p.filename == NULL);
}

TEST(getparams, change_from_and_order)
{
    Params p;
    char *argv[] = { "ask", "--right2left", "--random", "input.txt", NULL };
    int argc = NELEMS(argv) - 1; /* NULL is not counted */
    int i;

    i = getparams(argc, argv, &p);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(RIGHT, p.from);
    TEST_ASSERT_EQUAL_INT(RANDOM, p.order);
    TEST_ASSERT_EQUAL_STRING("input.txt", p.filename);
}

TEST(getparams, unknown_option)
{
    Params p;
    char *argv[] = { "ask", "--right2left", "--unknown", "input.txt", NULL };
    int argc = NELEMS(argv) - 1; /* NULL is not counted */
    int i;

    i = getparams(argc, argv, &p);
    TEST_ASSERT_EQUAL_INT(0, i);
    TEST_ASSERT_EQUAL_STRING("unknown option: --unknown", err_msg);
}
