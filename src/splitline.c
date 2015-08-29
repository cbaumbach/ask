#include "splitline.h"
#include "err_msg.h"
#include <string.h>

static int space_only(const char *s);

int splitline(char *line, char **left, char **right)
{
    char *p;

    p = line;

    if (*p == '\0') {
        set_err_msg("line was empty");
        return 0;
    }

    /* Terminate 1st column by overwriting tab with NUL character. */
    while (*p != '\t'  &&  *p != '\0')
        ++p;
    if (*p == '\t')
        *p = '\0';
    else {
        set_err_msg("line contains no tab separator: |%s|", line);
        return 0;
    }

    *left = line;
    *right = ++p;

    if (strlen(*left) == 0) {
        set_err_msg("missing left column: |%c%s|", '\t', *right);
        return 0;
    }
    if (strlen(*right) == 0) {
        set_err_msg("missing right column: |%s%c|", *left, '\t');
        return 0;
    }
    if (space_only(*left)) {
        set_err_msg("left column consists only of spaces: |%s%c%s|",
            *left, '\t', *right);
        return 0;
    }
    if (space_only(*right)) {
        set_err_msg("right column consists only of spaces: |%s%c%s|",
            *left, '\t', *right);
        return 0;
    }

    return 1;
}

static int space_only(const char *s)
{
    while (*s != '\0')
        if (*s++ != ' ')        /* found a non-space */
            return 0;

    return 1;
}
