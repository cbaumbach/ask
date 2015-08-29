#include "getparams.h"
#include "from.h"
#include <string.h>
#include "err_msg.h"
#include <stdlib.h>

Params initparams(void)
{
    Params p;

    p.help = 0;
    p.from = LEFT;
    p.order = ASIS;
    p.maxtry = 1;
    p.filename = NULL;

    return p;
}

int getparams(int argc, char **argv, Params *p)
{
    int i;
    char *s;

    *p = initparams();

    i = 1;                      /* skip program name */
    while (i < argc - 1) {      /* stop when filename is reached */
#define IS(opt) strcmp(opt, argv[i]) == 0
#define HAS(opt) strstr(argv[i], opt) == argv[i]
        if (IS("--help"))
            p->help = 1;
        else if (IS("--left2right"))
            p->from = LEFT;
        else if (IS("--right2left"))
            p->from = RIGHT;
        else if (HAS("--try=")) {
            s = strstr(argv[i], "=");
            p->maxtry = atoi(++s);
        }
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
