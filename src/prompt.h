#ifndef PROMPT_H
#define PROMPT_H

#include "makeentry.h"

const char *prompt(Entry e, int dir);
int correct(const char *answer, Entry e, int from);

#endif
