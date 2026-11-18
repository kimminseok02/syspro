
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid1, pid2;

    printf("[PARENT] : Hello, world ! pid=%d\n",
           getpid());
    fflush(stdout);

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        printf("[Child 1] : Hello, world ! pid=%d\n",
               getpid());
        exit(0);
    }

    waitpid(pid1, NULL, 0);

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        printf("[Child 2] : Hello, world ! pid=%d\n",
               getpid());
        exit(0);
    }

    waitpid(pid2, NULL, 0);

    return 0;
}

