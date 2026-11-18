
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid;

    printf("[%d] Process start\n", getpid());
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    printf("[%d] Process : return value %d\n",
           getpid(), pid);

    if (pid > 0) {
        wait(NULL);
    }

    return 0;
}

