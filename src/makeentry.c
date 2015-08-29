#include "makeentry.h"

Entry makeentry(const char *left, const char *right)
{
    Entry e;

    e.passed = 0;
    e.left = left;
    e.right = right;

    return e;
}
