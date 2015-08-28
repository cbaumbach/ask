#ifndef ERR_MSG_H
#define ERR_MSG_H

#include <stdio.h>

#define set_err_msg(...) snprintf(err_msg, ERR_MSG_MAX_LEN, __VA_ARGS__)
#define pr_err_msg() fprintf(stderr, "%s\n", err_msg)

enum { ERR_MSG_MAX_LEN = 200 };
extern char err_msg[];

#endif
