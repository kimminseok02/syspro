#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 100
#define MAX_LEN 100

int main(int argc, char *argv[])
{
    int fd;
    char text[MAX_LINES][MAX_LEN] = {0};
    char ch;
    int line = 0;
    int pos = 0;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            text[line][pos] = '\0';
            line++;
            pos = 0;
        }
        else {
            text[line][pos++] = ch;
        }
    }

    if (pos > 0) {
        text[line][pos] = '\0';
        line++;
    }

    close(fd);

    for (int i = line - 1; i >= 0; i--)
        printf("%s\n", text[i]);

    return 0;
}
