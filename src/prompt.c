#include "prompt.h"
#include "from.h"
#include <stdlib.h>
#include <string.h>

const char *prompt(Entry e, int dir)
{
    return (dir == LEFT) ? e.left : e.right;
}

int correct(const char *answer, Entry e, int from)
{
    return strcmp(answer, (from == LEFT) ? e.right : e.left) == 0;
}
