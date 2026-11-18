
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid1, child;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args]\n",
                argv[0]);
        return 1;
    }

    pid1 = fork();

    if (pid1 == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: execute failed\n", argv[1]);
        exit(1);
    }
    else if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    child = wait(&status);

    if (child < 0) {
        perror("wait");
        return 1;
    }

    printf("[%d] child process %d end\n",
           getpid(), child);

    if (WIFEXITED(status)) {
        printf("        end code %d\n",
               WEXITSTATUS(status));
    }

    return 0;
}

