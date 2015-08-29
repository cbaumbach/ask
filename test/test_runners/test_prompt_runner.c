#include "unity_fixture.h"

TEST_GROUP_RUNNER(prompt)
{
    RUN_TEST_CASE(prompt, left);
    RUN_TEST_CASE(prompt, right);
    RUN_TEST_CASE(prompt, compare_with_left);
    RUN_TEST_CASE(prompt, compare_with_right);
    RUN_TEST_CASE(prompt, fail_with_left);
    RUN_TEST_CASE(prompt, fail_with_right);
}
