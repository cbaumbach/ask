#include "sort.h"
#include <string.h>
#include <stdlib.h>

int by_left(Entry *s, Entry *t)
{
    return strcmp(s->left, t->left);
}

int by_right(Entry *s, Entry *t)
{
    return strcmp(s->right, t->right);
}

int by_chance(Entry *s, Entry *t)
{
    int r = rand();
    int i = strcmp(s->right, t->right);

    if (i == 0)
        return 0;
    else if (r % 2 == 0)
        return -1;
    else
        return 1;
}
