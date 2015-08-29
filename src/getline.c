#include "getline.h"
#include <stdio.h>
#include <stdlib.h>
#include "err_msg.h"

int getline(char **line, FILE *fp)
{
    int c;
    char *buf;       /* line buffer */
    int n = 2;                /* initial size of line buffer */
    int nc;                   /* number of characters stored so far */
    char *p;

    /* Allocate space for line buffer. */
    if ((buf = malloc(n * sizeof(char))) == NULL) {
        set_err_msg("failed to malloc %lu bytes",
            (unsigned long) n * sizeof(char));
        return 0;
    }

    nc = 0;
    while ((c = getc(fp)) != EOF  &&  c != '\n') {
        if (nc >= n - 1) {      /* line buffer is full */
            n *= 2;             /* double line buffer size */
            if ((p = realloc(buf, n * sizeof(char))) == NULL) {
                set_err_msg("failed to realloc %lu bytes",
                    (unsigned long) n * sizeof(char));
                return 0;
            }
            buf = p;
        }
        buf[nc++] = c;
    }
    if (c == '\n')
        buf[nc++] = '\0';             /* terminate string */

    *line = buf;

    return nc;
}
