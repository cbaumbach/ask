#include <stdio.h>
#include <stdlib.h>
#include "getline.h"
#include "err_msg.h"
#include "makeentry.h"
#include "insert.h"
#include "splitline.h"

void usage(const char *progname);

int main(int argc, char **argv)
{
    char *filename;
    int nline;                  /* number of lines read */
    int i;
    FILE *fp;
    char *line, *left, *right;
    Entry e;
    Tab tab;

    if (argc != 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    filename = argv[1];
    if ((fp = fopen(filename, "rb")) == NULL) {
        set_err_msg("failed to open file: %s", filename);
        pr_err_msg();
        exit(EXIT_FAILURE);
    }

    tab = maketab();
    nline = 0;
    while (getline(&line, fp)) {
        ++nline;
        if (!splitline(line, &left, &right)) {
            fprintf(stderr, "skipping line %d: |%s|\n",
                nline, line);
            continue;
        }
        e = makeentry(left, right);
        if (!insert(&tab, e)) {
            pr_err_msg();
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(fp)) {
        set_err_msg("failed to close file: %s", filename);
        pr_err_msg();
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < tab.n; i++) {
        e = tab.e[i];
        printf("entry %d: %10s %10s %10d\n", i, e.left, e.right,
            e.passed);
    }

    exit(EXIT_SUCCESS);
}

void usage(const char *progname)
{
    fprintf(stderr, "usage: %s file\n", progname);
}
