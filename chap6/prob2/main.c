
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s mode file\n", argv[0]);
        return 1;
    }

    int mode = (int)strtol(argv[1], NULL, 8);

    if (chmod(argv[2], mode) == -1) {
        perror(argv[2]);
        return 1;
    }

    return 0;
}

