
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid, child, status;

    printf("[%d] parental process start\n", getpid());
    fflush(stdout);

    pid = fork();

    if (pid == 0) {
        printf("[%d] child process start\n", getpid());
        exit(1);
    }
    else if (pid > 0) {
        child = wait(&status);

        printf("[%d] child process %d end\n",
               getpid(), child);
        printf("        end code %d\n", status >> 8);
    }
    else {
        perror("fork");
        return 1;
    }

    return 0;
}

