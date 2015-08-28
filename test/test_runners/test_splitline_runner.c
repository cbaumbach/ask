#include "unity_fixture.h"

TEST_GROUP_RUNNER(splitline)
{
    RUN_TEST_CASE(splitline, valid_line);
    RUN_TEST_CASE(splitline, empty_line);
    RUN_TEST_CASE(splitline, line_without_tab);
    RUN_TEST_CASE(splitline, missing_right);
    RUN_TEST_CASE(splitline, missing_left);
    RUN_TEST_CASE(splitline, space_only_left_column);
}
