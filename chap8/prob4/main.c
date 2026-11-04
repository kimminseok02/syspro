#include <stdio.h>
#include <stdlib.h>

static void exit_handler1(void);
static void exit_handler2(void);

int main(void)
{
    if (atexit(exit_handler1) != 0) {
        perror("exit_handler1 등록 실패");
        return 1;
    }

    if (atexit(exit_handler2) != 0) {
        perror("exit_handler2 등록 실패");
        return 1;
    }

    printf("main 끝\n");

    return 0;
}

static void exit_handler1(void)
{
    printf("첫 번째 exit 처리기\n");
}

static void exit_handler2(void)
{
    printf("두 번째 exit 처리기\n");
}
