#include "splitline.h"
#include "err_msg.h"

int splitline(char *line, char **left, char **right)
{
    char *p;

    /* Terminate first column with NUL character. */
    p = line;
    while (*p != '\t'  &&  *p != '\0')
        ++p;
    if (*p == '\t')
        *p = '\0';
    else {
        set_err_msg("line was empty");
        return 0;
    }

    *left = line;
    *right = ++p;

    return 1;
}
