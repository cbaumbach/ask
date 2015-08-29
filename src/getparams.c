#include "getparams.h"
#include "from.h"
#include <string.h>
#include "err_msg.h"

Params initparams(void)
{
    Params p;

    p.from = LEFT;
    p.order = ASIS;
    p.filename = NULL;

    return p;
}

int getparams(int argc, char **argv, Params *p)
{
    int i;

    *p = initparams();

    i = 1;                      /* skip program name */
    while (i < argc - 1) {      /* stop when filename is reached */
#define IS(opt) strcmp(opt, argv[i]) == 0
        if (IS("--left2right"))
            p->from = LEFT;
        else if (IS("--right2left"))
            p->from = RIGHT;
        else if (IS("--random"))
            p->order = RANDOM;
        else if (IS("--as-is"))
            p->order = ASIS;
        else if (IS("--lsort"))
            p->order = LSORT;
        else if (IS("--rsort"))
            p->order = RSORT;
        else {
            set_err_msg("unknown option: %s", argv[i]);
            return 0;
        }
#undef IS
        ++i;
    }
    p->filename = argv[i];

    return 1;
}
