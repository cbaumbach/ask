#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(getline);
    RUN_TEST_GROUP(splitline);
    RUN_TEST_GROUP(makeentry);
    RUN_TEST_GROUP(insert);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
