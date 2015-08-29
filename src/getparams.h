#ifndef GETPARAMS_H
#define GETPARAMS_H

enum {
    ASIS,
    RANDOM,
    LSORT,
    RSORT
};

struct params {
    int help;                   /* display help message */
    int from;                   /* LEFT RIGTH */
    int order;                  /* ASIS RANDOM LSORT RSORT */
    int maxtry;    /* number of tries until correct answer is shown */
    const char *filename;       /* name of input file */
};

typedef struct params Params;

Params initparams(void);
int getparams(int argc, char **argv, Params *p);

#endif
