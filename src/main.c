#include <stdio.h>
#include <stdlib.h>
#include "getline.h"
#include "err_msg.h"
#include "makeentry.h"
#include "insert.h"
#include "splitline.h"
#include "prompt.h"
#include "getparams.h"
#include "from.h"
#include "sort.h"
#include <time.h>

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

    if (params.help) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
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

    /* ============================================================
       Ask user for translations.
       ============================================================ */

    switch(params.order) {
    case ASIS:
        /* nothing to do */
        break;
    case RANDOM:
        /* randomize order of entries */
        srand((unsigned) time(NULL));
        qsort(tab.e, tab.n, sizeof(Entry), by_chance);
        break;
    case LSORT:
        /* sort entries by left column */
        qsort(tab.e, tab.n, sizeof(Entry), by_left);
        break;
    case RSORT:
        /* sort entries by right column */
        qsort(tab.e, tab.n, sizeof(Entry), by_right);
        break;
    default:
        set_err_msg("can't happen");
        pr_err_msg();
        exit(EXIT_FAILURE);
    }

    npassed = 0;
    i = 0;
    while (npassed < tab.n) {
        ep = &tab.e[i++];
        if (ep->passed)
            continue;
        printf("> %s\n", prompt(*ep, params.from));
        printf("? ");
        fflush(stdout);
        if (!getline(&answer, stdin)) {
            pr_err_msg();
            continue;
        }
        if (correct(answer, *ep, params.from)) {
            ep->passed = 1;
            ++npassed;
        }
        else if (++ep->ntry >= params.maxtry) {
            ep->ntry = 0;       /* reset */
            printf("! %s\n",
                (params.from == LEFT) ? ep->right : ep->left);
        }
        i %= tab.n;
    }

    freetab(&tab);

    exit(EXIT_SUCCESS);
}

void usage(const char *progname)
{
    fprintf(stderr,
        "Usage: %s [OPTIONS] file\n"
        "\n"
        "OPTIONS:\n"
        "\n"
        "  --help          display this help message\n"
        "  --left2right    ask from left to right (default)\n"
        "  --right2left    ask from right to left\n"
        "  --try=K         if user fails to give the correct\n"
        "                  answer to a question K times in a\n"
        "                  row, display the correct answer\n"
        "                  (default: 1)\n"
        "  --as-is         use order in input file (default)\n"
        "  --random        use random order\n"
        "  --lsort         sort by left column\n"
        "  --rsort         sort by right column\n",
        progname);
}
