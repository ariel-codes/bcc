#include <stdlib.h>

#include "stacks.h"

Stack *stk_create()
{
    Stack *p = malloc(sizeof(Stack));
    p->top = NULL;
    p->heigh = 0;
    return p;
}

SItem *stk_push(Stack *p, Queue *l)
{
    SItem *new = malloc(sizeof(SItem));
    new->under = p->top;
    p->top = new;
    p->heigh++;
    return new;
}

Queue *stk_pop(Stack *p)
{
    if (!p->heigh)
        return NULL;
    SItem *drop = p->top;
    Queue *item = drop->region;
    p->top = p->top->under;
    p->heigh--;
    free(drop);
    return item;
}