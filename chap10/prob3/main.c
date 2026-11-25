
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[32] = "Do you like Linux?";
    char *ptr, *p;

    ptr = (char *)malloc(32);

    if (ptr == NULL) {
        perror("malloc");
        exit(1);
    }

    memcpy(ptr, str, strlen(str) + 1);
    puts(ptr);

    memset(ptr + 12, 'l', 1);
    puts(ptr);

    p = (char *)memchr(ptr, 'l', 18);
    puts(p);

    memmove(str + 12, str + 7, 10);
    puts(str);

    free(ptr);

    return 0;
}

