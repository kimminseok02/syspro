
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main()
{
    int count = 0, id;
    char name[20];
    struct student *p, *head = NULL;

    printf("학번과 이름을 입력하세요\n");

    while (scanf("%d %19s", &id, name) == 2) {
        p = (struct student *)malloc(sizeof(struct student));

        if (p == NULL) {
            perror("malloc");
            exit(1);
        }

        p->id = id;
        strcpy(p->name, name);
        p->next = head;
        head = p;
    }

    printf("\n* 학생 정보(역순) *\n");

    p = head;

    while (p != NULL) {
        count++;
        printf("학번: %d 이름: %s\n", p->id, p->name);
        head = p->next;
        free(p);
        p = head;
    }

    printf("총 %d 명입니다.\n", count);

    return 0;
}

