#ifndef GETPARAMS_H
#define GETPARAMS_H

enum {
    ASIS,
    RANDOM,
    LSORT,
    RSORT
};

struct params {
    int from;                   /* LEFT RIGTH */
    int order;                  /* ASIS RANDOM LSORT RSORT */
    const char *filename;       /* name of input file */
};

typedef struct params Params;

Params initparams(void);
int getparams(int argc, char **argv, Params *p);

#endif
