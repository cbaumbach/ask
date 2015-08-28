#include <stdio.h>
#include <stdlib.h>
#include "getline.h"
#include "err_msg.h"

void usage(const char *progname);

int main(int argc, char **argv)
{
    char *filename;
    int nline;                  /* number of lines read */
    FILE *fp;
    char *line;

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

    nline = 0;
    while (getline(&line, fp))
        printf("line %d: %s\n", ++nline, line);

    if (fclose(fp)) {
        set_err_msg("failed to close file: %s", filename);
        pr_err_msg();
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void usage(const char *progname)
{
    fprintf(stderr, "usage: %s file\n", progname);
}
