#include "unity_fixture.h"
#include "splitline.h"
#include "err_msg.h"
#include <string.h>

TEST_GROUP(splitline);

TEST_SETUP(splitline)
{
}

TEST_TEAR_DOWN(splitline)
{
}

TEST(splitline, valid_line)
{
    char the_line[] = "left\tright";
    char *line;
    char *left = NULL;
    char *right = NULL;
    int i = -1;
    size_t n;

    n = (strlen(the_line) + 1) * sizeof(char);
    if ((line = malloc(n)) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n);
        pr_err_msg();
        TEST_FAIL();
    }
    strcpy(line, the_line);

    i = splitline(line, &left, &right);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_TRUE(left != NULL);
    TEST_ASSERT_TRUE(right != NULL);
    TEST_ASSERT_EQUAL_STRING("left", left);
    TEST_ASSERT_EQUAL_STRING("right", right);

    free(line);
}

TEST(splitline, empty_line)
{
    char the_line[] = "";
    char *line;
    char *left = NULL;
    char *right = NULL;
    int i = -1;
    size_t n;

    n = (strlen(the_line) + 1) * sizeof(char);
    if ((line = malloc(n)) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n);
        pr_err_msg();
        TEST_FAIL();
    }
    strcpy(line, the_line);

    i = splitline(line, &left, &right);
    TEST_ASSERT_EQUAL_INT(0, i);
    TEST_ASSERT_EQUAL_STRING("line was empty", err_msg);

    free(line);
}

TEST(splitline, line_without_tab)
{
    char the_line[] = "left right";
    char *line;
    char *left = NULL;
    char *right = NULL;
    int i = -1;
    size_t n;

    n = (strlen(the_line) + 1) * sizeof(char);
    if ((line = malloc(n)) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n);
        pr_err_msg();
        TEST_FAIL();
    }
    strcpy(line, the_line);

    i = splitline(line, &left, &right);
    TEST_ASSERT_EQUAL_INT(0, i);
    TEST_ASSERT_EQUAL_STRING("line contains no tab separator: |left right|", err_msg);

    free(line);
}

TEST(splitline, missing_right)
{
    char the_line[] = "left\t";
    char *line;
    char *left = NULL;
    char *right = NULL;
    int i = -1;
    size_t n;

    n = (strlen(the_line) + 1) * sizeof(char);
    if ((line = malloc(n)) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n);
        pr_err_msg();
        TEST_FAIL();
    }
    strcpy(line, the_line);

    i = splitline(line, &left, &right);
    TEST_ASSERT_EQUAL_INT(0, i);
    TEST_ASSERT_EQUAL_STRING("missing right column: |left\t|", err_msg);

    free(line);
}

TEST(splitline, missing_left)
{
    char the_line[] = "\tright";
    char *line;
    char *left = NULL;
    char *right = NULL;
    int i = -1;
    size_t n;

    n = (strlen(the_line) + 1) * sizeof(char);
    if ((line = malloc(n)) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n);
        pr_err_msg();
        TEST_FAIL();
    }
    strcpy(line, the_line);

    i = splitline(line, &left, &right);
    TEST_ASSERT_EQUAL_INT(0, i);
    TEST_ASSERT_EQUAL_STRING("missing left column: |\tright|", err_msg);

    free(line);
}
