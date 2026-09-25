#include <stdio.h>
#include <string.h>
#include "copy.h"

int main()
{
    char str[5][MAXLINE];
    char temp[MAXLINE];
    int i = 0;
    int j;

    while (i < 5) {
        fgets(str[i], MAXLINE, stdin);
        str[i][strcspn(str[i], "\n")] = '\0';
        i++;
    }

    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 5; j++) {
            if (strlen(str[i]) < strlen(str[j])) {
                copy(str[i], temp);
                copy(str[j], str[i]);
                copy(temp, str[j]);
            }
        }
    }

    for (i = 0; i < 5; i++)
        printf("%s\n", str[i]);

    return 0;
}
