
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("parental process start\n");
    fflush(stdout);

    pid = fork();

    if (pid == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "first execute failed\n");
        exit(1);
    }
    else if (pid < 0) {
        perror("fork");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "second execute failed\n");
        exit(2);
    }
    else if (pid < 0) {
        perror("fork");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "third execute failed\n");
        exit(3);
    }
    else if (pid < 0) {
        perror("fork");
        return 1;
    }

    printf("parental process end\n");

    return 0;
}

