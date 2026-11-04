#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *home = getenv("HOME");
    char *shell = getenv("SHELL");
    char *path = getenv("PATH");

    printf("HOME = %s\n", home != NULL ? home : "(not set)");
    printf("SHELL = %s\n", shell != NULL ? shell : "(not set)");
    printf("PATH = %s\n", path != NULL ? path : "(not set)");

    return 0;
}
