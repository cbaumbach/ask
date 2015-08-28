#include "unity_fixture.h"
#include "err_msg.h"
#include "getline.h"
#include <stdio.h>
#include <stdlib.h>

TEST_GROUP(getline);

static FILE *fp;
static char *non_empty_file = "test/test_data/getline_non_empty.txt";
static char *empty_file = "test/test_data/getline_empty.txt";
static int i;

TEST_SETUP(getline)
{
}

TEST_TEAR_DOWN(getline)
{
}

TEST(getline, empty_file)
{
    char *line;

    if ((fp = fopen(empty_file, "rb")) == NULL) {
        set_err_msg("failed to open file: %s", non_empty_file);
        pr_err_msg();
        TEST_FAIL();
    }

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(0, i);

    if (fclose(fp)) {
        set_err_msg("failed to close file: %s", non_empty_file);
        pr_err_msg();
        TEST_FAIL();
    }
}

TEST(getline, non_empty_file)
{
    char *line;

    if ((fp = fopen(non_empty_file, "rb")) == NULL) {
        set_err_msg("failed to open file: %s", non_empty_file);
        pr_err_msg();
        TEST_FAIL();
    }

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(9, i);
    TEST_ASSERT_EQUAL_STRING("one	eins", line);

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(9, i);
    TEST_ASSERT_EQUAL_STRING("two	zwei", line);

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(11, i);
    TEST_ASSERT_EQUAL_STRING("three	drei", line);

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_STRING("", line);

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(11, i);
    TEST_ASSERT_EQUAL_STRING("five	fuenf", line);

    i = getline(&line, fp);
    TEST_ASSERT_EQUAL_INT(0, i);

    if (fclose(fp)) {
        set_err_msg("failed to close file: %s", non_empty_file);
        pr_err_msg();
        TEST_FAIL();
    }
}
