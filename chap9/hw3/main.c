
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void execute_command(char *command)
{
    char *args[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;
    char *token, *saveptr = NULL;
    int argc = 0, background = 0;
    pid_t pid;

    token = strtok_r(command, " \t\n", &saveptr);

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            input_file = strtok_r(NULL, " \t\n", &saveptr);

            if (input_file == NULL) {
                fprintf(stderr, "input file missing\n");
                return;
            }
        }
        else if (strcmp(token, ">") == 0) {
            output_file = strtok_r(NULL, " \t\n", &saveptr);

            if (output_file == NULL) {
                fprintf(stderr, "output file missing\n");
                return;
            }
        }
        else if (strcmp(token, "&") == 0) {
            background = 1;
        }
        else {
            if (argc >= MAX_ARGS - 1) {
                fprintf(stderr, "too many arguments\n");
                return;
            }
            args[argc++] = token;
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    if (argc == 0)
        return;

    args[argc] = NULL;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        int fd;

        if (input_file != NULL) {
            fd = open(input_file, O_RDONLY);

            if (fd < 0) {
                perror("open input");
                _exit(1);
            }

            if (dup2(fd, STDIN_FILENO) < 0) {
                perror("dup2 input");
                _exit(1);
            }

            close(fd);
        }

        if (output_file != NULL) {
            fd = open(output_file,
                      O_WRONLY | O_CREAT | O_TRUNC, 0666);

            if (fd < 0) {
                perror("open output");
                _exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("dup2 output");
                _exit(1);
            }

            close(fd);
        }

        execvp(args[0], args);
        perror(args[0]);
        _exit(127);
    }

    if (background) {
        printf("[background] PID=%d\n", (int)pid);
    }
    else {
        while (waitpid(pid, NULL, 0) == -1 &&
               errno == EINTR) {
        }
    }
}

int main(void)
{
    char line[MAX_LINE];
    char *command, *saveptr;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        if (strcmp(line, "exit\n") == 0 ||
            strcmp(line, "exit") == 0)
            break;

        saveptr = NULL;
        command = strtok_r(line, ";", &saveptr);

        while (command != NULL) {
            execute_command(command);
            command = strtok_r(NULL, ";", &saveptr);
        }
    }

    return 0;
}

