#include "unity_fixture.h"

TEST_GROUP_RUNNER(getparams)
{
    RUN_TEST_CASE(getparams, initparams);
    RUN_TEST_CASE(getparams, change_from_and_order);
}
