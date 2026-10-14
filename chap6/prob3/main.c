
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[])
{
    struct stat buf;
    struct utimbuf time;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &buf) == -1) {
        perror("stat");
        return 1;
    }

    time.actime = buf.st_atime;
    time.modtime = buf.st_mtime;

    if (utime(argv[2], &time) == -1) {
        perror("utime");
        return 1;
    }

    return 0;
}

