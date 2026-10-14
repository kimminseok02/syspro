
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buffer[1024];
    ssize_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s link\n", argv[0]);
        return 1;
    }

    nread = readlink(argv[1], buffer, sizeof(buffer));

    if (nread == -1) {
        perror("readlink");
        return 1;
    }

    if (write(1, buffer, nread) == -1) {
        perror("write");
        return 1;
    }

    write(1, "\n", 1);

    return 0;
}

