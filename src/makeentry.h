#ifndef MAKEENTRY_H
#define MAKEENTRY_H

struct entry {
    const char *left;
    const char *right;
    int ntry;
    int passed;
};

typedef struct entry Entry;

Entry makeentry(const char *left, const char *right);

#endif
