
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("[Child] : Hello, world pid=%d\n",
               getpid());
    }
    else {
        printf("[Parent] : Hello, world pid=%d\n",
               getpid());
        wait(NULL);
    }

    return 0;
}

