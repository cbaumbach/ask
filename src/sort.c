#include "sort.h"
#include <string.h>
#include <stdlib.h>

int by_left(const void *s, const void *t)
{
    Entry *e1 = (Entry *) s;
    Entry *e2 = (Entry *) t;

    return strcmp(e1->left, e2->left);
}

int by_right(const void *s, const void *t)
{
    Entry *e1 = (Entry *) s;
    Entry *e2 = (Entry *) t;

    return strcmp(e1->right, e2->right);
}

int by_chance(const void *s, const void *t)
{
    Entry *e1 = (Entry *) s;
    Entry *e2 = (Entry *) t;
    int r = rand();
    int i = strcmp(e1->right, e2->right);

    if (i == 0)
        return 0;
    else if (r % 2 == 0)
        return -1;
    else
        return 1;
}
