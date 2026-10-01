#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int i;
    int c;
    int line = 1;
    int line_start = 1;
    int number = 0;
    int start = 1;

    if (argc < 2) {
        fprintf(stderr, "How to use: %s [-n] file...\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-n") == 0) {
        number = 1;
        start = 2;

        if (argc < 3) {
            fprintf(stderr, "How to use: %s -n file...\n", argv[0]);
            return 1;
        }
    }

    for (i = start; i < argc; i++) {
        fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "Error Open File: %s\n", argv[i]);
            continue;
        }

        while ((c = fgetc(fp)) != EOF) {
            if (number && line_start) {
                printf("%6d\t", line++);
                line_start = 0;
            }

            putchar(c);

            if (c == '\n')
                line_start = 1;
        }

        fclose(fp);
    }

    return 0;
}
