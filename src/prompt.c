#include "prompt.h"
#include <stdlib.h>

const char *prompt(Entry e, int dir)
{
    return (dir == LEFT) ? e.left : e.right;
}
