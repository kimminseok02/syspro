
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int mysystem(const char *cmdstring)
{
    int pid, status;

    if (cmdstring == NULL)
        return 1;

    pid = fork();

    if (pid == -1)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring,
              (char *)0);
        _exit(127);
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR)
                return -1;
        }
        else {
            return status;
        }
    } while (1);
}

int main(void)
{
    int status;

    status = mysystem("date");
    if (status < 0)
        perror("system() error");
    else
        printf("end code %d\n", WEXITSTATUS(status));
    fflush(stdout);

    status = mysystem("hello");
    if (status < 0)
        perror("system() error");
    else
        printf("end code %d\n", WEXITSTATUS(status));
    fflush(stdout);

    status = mysystem("who; exit 44");
    if (status < 0)
        perror("system() error");
    else
        printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}

