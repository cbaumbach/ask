#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(getline);
    RUN_TEST_GROUP(splitline);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
