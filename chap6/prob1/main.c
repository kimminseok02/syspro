
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &buf) < 0) {
            perror("stat()");
            continue;
        }

        printf("%s: ", argv[i]);

        if (S_ISREG(buf.st_mode)) {
            printf("Ordinary File\n");
        }
        else if (S_ISDIR(buf.st_mode)) {
            printf("Directory\n");
        }
        else if (S_ISCHR(buf.st_mode)) {
            printf("Character Device File\n");
        }
        else if (S_ISBLK(buf.st_mode)) {
            printf("Block Device File\n");
        }
        else if (S_ISFIFO(buf.st_mode)) {
            printf("FIFO File\n");
        }
        else if (S_ISLNK(buf.st_mode)) {
            printf("Symbolic Link\n");
        }
        else if (S_ISSOCK(buf.st_mode)) {
            printf("Socket\n");
        }
    }

    return 0;
}

