#include "makeentry.h"
#include <stdlib.h>

Entry makeentry(const char *left, const char *right)
{
    Entry e;

    e.ntry = 0;
    e.passed = 0;
    e.left = left;
    e.right = right;

    return e;
}

void freeentry(Entry *e)
{
    free((void *)e->left);
    e->left = NULL;
    e->right = NULL;
}
