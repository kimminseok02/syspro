
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    printf("PARENT: PID = %d GID = %d\n",
           getpid(), getpgrp());
    fflush(stdout);

    pid = fork();

    if (pid == 0) {
        printf("CHILD: PID = %d GID = %d\n",
               getpid(), getpgrp());
        exit(0);
    }
    else if (pid > 0) {
        waitpid(pid, NULL, 0);
    }
    else {
        perror("fork");
        return 1;
    }

    return 0;
}

