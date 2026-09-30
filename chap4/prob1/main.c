#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc < 2)
        fp = stdin;
    else
        fp = fopen(argv[1], "r");

    c = fgetc(fp);

    while (c != EOF) {
        fputc(c, stdout);
        c = fgetc(fp);
    }

    fclose(fp);

    return 0;
}
