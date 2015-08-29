#include "unity_fixture.h"

TEST_GROUP_RUNNER(insert)
{
    RUN_TEST_CASE(insert, maketab);
    RUN_TEST_CASE(insert, empty_table);
}
