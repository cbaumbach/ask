#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(getline);
    RUN_TEST_GROUP(splitline);
    RUN_TEST_GROUP(makeentry);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
