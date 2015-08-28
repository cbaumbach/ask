#include "unity_fixture.h"

TEST_GROUP_RUNNER(splitline)
{
    RUN_TEST_CASE(splitline, valid_line);
    RUN_TEST_CASE(splitline, empty_line);
}
