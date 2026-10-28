
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s File\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");

    while (scanf("%d", &id) == 1) {
        if (id < START_ID) {
            printf("No record %d\n", id);
            printf("\nEnter StudentID you want to modify : ");
            continue;
        }

        off_t position = (off_t)(id - START_ID) * sizeof(record);

        lseek(fd, position, SEEK_SET);

        if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
            perror(argv[1]);
            close(fd);
            exit(3);
        }

        if (read(fd, &record, sizeof(record)) == sizeof(record)
            && record.id == id) {

            printf("Name:%s\t StuID:%d\t Score:%d\n",
                   record.name, record.id, record.score);

            printf("Enter new score: ");

            if (scanf("%d", &record.score) != 1) {
                lseek(fd, position, SEEK_SET);
                lockf(fd, F_ULOCK, sizeof(record));
                break;
            }

            lseek(fd, position, SEEK_SET);
            write(fd, &record, sizeof(record));
        } else {
            printf("No record %d\n", id);
        }

        lseek(fd, position, SEEK_SET);

        if (lockf(fd, F_ULOCK, sizeof(record)) == -1) {
            perror(argv[1]);
            close(fd);
            exit(3);
        }

        printf("\nEnter StudentID you want to modify : ");
    }

    close(fd);
    return 0;
}

