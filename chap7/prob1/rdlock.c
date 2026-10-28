
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;
    struct flock lock = {0};

    if (argc < 2) {
        fprintf(stderr, "How to use : %s File\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID to search : ");

    while (scanf("%d", &id) == 1) {
        if (id < START_ID) {
            printf("No record %d\n", id);
            printf("\nEnter StudentID to search : ");
            continue;
        }

        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (off_t)(id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);

        if (fcntl(fd, F_SETLKW, &lock) == -1) {
            perror(argv[1]);
            close(fd);
            exit(3);
        }

        lseek(fd, lock.l_start, SEEK_SET);

        if (read(fd, &record, sizeof(record)) == sizeof(record)
            && record.id == id) {

            printf("Name:%s\t StuID:%d\t Score:%d\n",
                   record.name, record.id, record.score);
        } else {
            printf("No record %d\n", id);
        }

        lock.l_type = F_UNLCK;

        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror(argv[1]);
            close(fd);
            exit(3);
        }

        printf("\nEnter StudentID to search : ");
    }

    close(fd);
    return 0;
}

