
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid, child, fd, status;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s outfile command [args]\n", argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);

        if (fd < 0) {
            perror("open");
            exit(1);
        }

        if (dup2(fd, 1) < 0) {
            perror("dup2");
            close(fd);
            exit(1);
        }

        close(fd);

        execvp(argv[2], &argv[2]);

        fprintf(stderr, "%s: execute failed\n", argv[2]);
        exit(127);
    }
    else {
        child = wait(&status);

        if (child < 0) {
            perror("wait");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("[%d] child process %d end\n",
                   getpid(), child);
        }
    }

    return 0;
}

