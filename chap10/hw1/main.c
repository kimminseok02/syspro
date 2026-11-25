
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data)
{
    struct node *p;

    p = (struct node *)malloc(sizeof(struct node));

    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    p->data = data;
    p->next = top->next;
    top->next = p;
}

int pop(struct node *top)
{
    struct node *p;
    int data;

    if (top->next == NULL)
        return -1;

    p = top->next;
    data = p->data;
    top->next = p->next;

    free(p);

    return data;
}

int main()
{
    struct node top;
    int data;

    top.next = NULL;

    while (scanf("%d", &data) == 1 && data > 0) {
        push(&top, data);
    }

    printf("Print stack\n");

    while (top.next != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}

