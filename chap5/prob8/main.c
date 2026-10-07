#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 100

int main(int argc, char *argv[])
{
    int fd;
    char savedText[MAX_LINES][MAX_LEN] = {0};
    char buf;
    char input[100];

    int line = 0;
    int pos = 0;
    int totalLine;
    ssize_t nread;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while ((nread = read(fd, &buf, 1)) > 0) {
        if (buf == '\n') {
            savedText[line][pos] = '\0';
            line++;
            pos = 0;
        }
        else {
            savedText[line][pos++] = buf;
        }
    }

    savedText[line][pos] = '\0';
    totalLine = line + 1;

    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", totalLine);
    printf("You can choose 1 ~ %d Line\n", totalLine);
    printf("Pls 'Enter' the line to select : ");

    scanf("%99s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLine; i++)
            printf("%s\n", savedText[i]);
    }

    else if (strchr(input, '-') != NULL) {
        int start, end;

        if (sscanf(input, "%d-%d", &start, &end) == 2) {
            for (int i = start; i <= end; i++) {
                if (i >= 1 && i <= totalLine)
                    printf("%s\n", savedText[i - 1]);
            }
        }
    }

    else if (strchr(input, ',') != NULL) {
        char *token;

        token = strtok(input, ",");

        while (token != NULL) {
            int num = atoi(token);

            if (num >= 1 && num <= totalLine)
                printf("%s\n", savedText[num - 1]);

            token = strtok(NULL, ",");
        }
    }

    else {
        int num = atoi(input);

        if (num >= 1 && num <= totalLine)
            printf("%s\n", savedText[num - 1]);
    }

    return 0;
}
