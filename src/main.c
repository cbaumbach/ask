#include <stdio.h>
#include <stdlib.h>
#include "getline.h"
#include "err_msg.h"
#include "makeentry.h"
#include "insert.h"
#include "splitline.h"
#include "prompt.h"
#include "getparams.h"

void usage(const char *progname);

int main(int argc, char **argv)
{
    char *filename;
    int nline;                  /* number of lines read */
    int npassed;          /* number of correctly answered questions */
    int i;
    FILE *fp;
    char *line, *left, *right, *answer;
    Entry e, *ep;
    Tab tab;
    Params params;

    if (!getparams(argc, argv, &params)) {
        pr_err_msg();
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* ============================================================
       Read entries from input file.
       ============================================================ */

    if ((fp = fopen(params.filename, "rb")) == NULL) {
        set_err_msg("failed to open file: %s", params.filename);
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

    npassed = 0;
    i = 0;
    while (npassed < tab.n) {
        ep = &tab.e[i++];
        if (ep->passed)
            continue;
        printf("> %s\n", prompt(*ep, LEFT));
        printf("? ");
        fflush(stdout);
        if (!getline(&answer, stdin)) {
            pr_err_msg();
            continue;
        }
        if (correct(answer, *ep, RIGHT)) {
            ep->passed = 1;
            ++npassed;
        }
        else
            printf("! %s\n", ep->right);
        i %= tab.n;
    }

    exit(EXIT_SUCCESS);
}

void usage(const char *progname)
{
    fprintf(stderr, "usage: %s file\n", progname);
}
