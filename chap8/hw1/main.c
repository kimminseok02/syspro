#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s [-e [name] | -u | -g | -i | -p]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc >= 3) {
            char *value = getenv(argv[2]);

            if (value != NULL) {
                printf("%s = %s\n", argv[2], value);
            } else {
                printf("환경변수를 찾을 수 없습니다.\n");
            }
        } else {
            for (char **env = environ; *env != NULL; env++) {
                printf("%s\n", *env);
            }
        }
    } else if (strncmp(argv[1], "-e", 2) == 0 && argv[1][2] != '\0') {
        char *name = argv[1] + 2;
        char *value = getenv(name);

        if (value != NULL) {
            printf("%s = %s\n", name, value);
        } else {
            printf("환경변수를 찾을 수 없습니다.\n");
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        printf("실제 사용자 ID : %d\n", getuid());
        printf("유효 사용자 ID : %d\n", geteuid());
    } else if (strcmp(argv[1], "-g") == 0) {
        printf("실제 그룹 ID : %d\n", getgid());
        printf("유효 그룹 ID : %d\n", getegid());
    } else if (strcmp(argv[1], "-i") == 0) {
        printf("프로세스 ID : %d\n", getpid());
    } else if (strcmp(argv[1], "-p") == 0) {
        printf("부모 프로세스 ID : %d\n", getppid());
    } else {
        printf("잘못된 옵션입니다.\n");
        return 1;
    }

    return 0;
}
