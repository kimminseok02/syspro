
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid1, pid2, child, status;

    printf("[%d] parental process start\n", getpid());
    fflush(stdout);

    pid1 = fork();

    if (pid1 == 0) {
        printf("[%d] child process[1] start\n", getpid());
        sleep(1);
        printf("[%d] child process[1] end\n", getpid());
        exit(1);
    }
    else if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    pid2 = fork();

    if (pid2 == 0) {
        printf("[%d] child process[2] start\n", getpid());
        sleep(2);
        printf("[%d] child process[2] end\n", getpid());
        exit(2);
    }
    else if (pid2 < 0) {
        perror("fork");
        return 1;
    }

    child = waitpid(pid1, &status, 0);

    if (child < 0) {
        perror("waitpid");
        return 1;
    }

    printf("[%d] child process[1] %d end\n",
           getpid(), child);
    printf("        end code %d\n", status >> 8);

    return 0;
}

