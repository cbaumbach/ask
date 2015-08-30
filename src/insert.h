#ifndef INSERT_H
#define INSERT_H

#include "makeentry.h"

struct tab {
    Entry *e;                   /* stored entries */
    int n;                      /* number of stored entries */
    int size;                   /* max number of entry slots */
};

typedef struct tab Tab;

Tab maketab(void);
int insert(Tab *tab, Entry e);
void freetab(Tab *tab);

#endif
