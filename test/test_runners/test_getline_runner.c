#include "unity_fixture.h"

TEST_GROUP_RUNNER(getline)
{
    RUN_TEST_CASE(getline, empty_file);
    RUN_TEST_CASE(getline, non_empty_file);
}
