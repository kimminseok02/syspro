#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    int c;

    if (argc != 3) {
        fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");

    if (fp1 == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 1;
    }

    fp2 = fopen(argv[2], "a");

    if (fp2 == NULL) {
        fprintf(stderr, "Error Open File\n");
        fclose(fp1);
        return 1;
    }

    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
