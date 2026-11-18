
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
        fprintf(stderr, "execute1 failed\n");
        exit(1);
    }
    else if (pid < 0) {
        perror("fork");
        return 1;
    }

    printf("prarental process end\n");

    return 0;
}

