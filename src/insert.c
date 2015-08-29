#include "insert.h"
#include "err_msg.h"
#include <stdlib.h>

Tab maketab(void)
{
    Tab t;

    t.e = NULL;
    t.n = 0;
    t.size = 0;

    return t;
}

int insert(Tab *t, Entry e)
{
    int n = t->n;
    int size = t->size;
    Entry *ep;

    /* Do we have enough space for another entry? */
    if (size < n + 1) {  /* not enough space */
        if (size == 0)
            size = n + 1;       /* use minimum necessary size */
        else
            size *= 2;    /* double number of available entry slots */
        if ((ep = realloc(t->e, size * sizeof(Entry))) == NULL) {
            set_err_msg("failed to realloc %lu bytes",
                (unsigned long) size * sizeof(Entry));
            return 0;
        }
        t->size = size;
        t->e = ep;
    }
    t->e[n] = e;
    ++t->n;

    return 1;
}
