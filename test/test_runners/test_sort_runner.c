#include "unity_fixture.h"

TEST_GROUP_RUNNER(sort)
{
    RUN_TEST_CASE(sort, by_left);
    RUN_TEST_CASE(sort, by_right);
}
