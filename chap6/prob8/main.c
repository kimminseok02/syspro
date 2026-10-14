
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s original link\n", argv[0]);
        return 1;
    }

    if (access(argv[1], F_OK) == -1) {
        perror(argv[1]);
        return 1;
    }

    if (symlink(argv[1], argv[2]) == -1) {
        perror("symlink");
        return 1;
    }

    return 0;
}

