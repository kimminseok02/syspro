
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXARG 64

int main(void)
{
    char line[MAXLINE];
    char *args[MAXARG];

    while (1) {
        char *token, *saveptr = NULL, *end;
        int argc = 0, background = 0;
        pid_t pid;

        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }

        printf("[Shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        end = line + strlen(line);

        while (end > line &&
               (end[-1] == '\n' ||
                end[-1] == ' ' ||
                end[-1] == '\t')) {
            end--;
        }

        if (end > line && end[-1] == '&') {
            background = 1;
            end--;
        }

        *end = '\0';

        token = strtok_r(line, " \t", &saveptr);

        while (token != NULL && argc < MAXARG - 1) {
            args[argc++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }

        if (token != NULL) {
            fprintf(stderr, "too many arguments\n");
            continue;
        }

        args[argc] = NULL;

        if (argc == 0)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        pid = fork();

        if (pid < 0) {
            perror("fork");
        }
        else if (pid == 0) {
            execvp(args[0], args);
            perror(args[0]);
            _exit(127);
        }
        else if (background) {
            printf("[background] PID=%d\n", (int)pid);
        }
        else {
            while (waitpid(pid, NULL, 0) == -1) {
                if (errno != EINTR) {
                    perror("waitpid");
                    break;
                }
            }
        }
    }

    return 0;
}

