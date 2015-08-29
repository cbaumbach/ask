#include "prompt.h"
#include <stdlib.h>
#include <string.h>

const char *prompt(Entry e, int dir)
{
    return (dir == LEFT) ? e.left : e.right;
}

int correct(const char *answer, Entry e, int dir)
{
    return strcmp(answer, (dir == LEFT) ? e.left : e.right) == 0;
}
