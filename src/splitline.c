#include "splitline.h"
#include "err_msg.h"

int splitline(char *line, char **left, char **right)
{
    char *p;

    /* Terminate first column with NUL character. */
    p = line;
    if (*p == '\0') {
        set_err_msg("line was empty");
        return 0;
    }
    else if (*p == '\t') {
        set_err_msg("missing left column: |%s|", line);
        return 0;
    }
    while (*p != '\t'  &&  *p != '\0')
        ++p;
    if (*p == '\t')
        *p = '\0';
    else {
        set_err_msg("line contains no tab separator: |%s|", line);
        return 0;
    }

    if (*++p == '\0') {
        set_err_msg("missing right column: |%s%c|", line, '\t');
        return 0;
    }

    *right = p;
    *left = line;

    /* Test whether left consists only of spaces. */
    p = *left;
    while (*p != '\0')
        if (*p != ' ')          /* found a non-space */
            break;
        else
            ++p;

    if (*p == '\0') {           /* no non-space found */
        set_err_msg("left column consists only of spaces: |%s%c%s|",
            *left, '\t', *right);
        return 0;
    }

    return 1;
}
