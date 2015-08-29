#ifndef PROMPT_H
#define PROMPT_H

#include "makeentry.h"

enum { LEFT, RIGHT };

const char *prompt(Entry e, int dir);

#endif
