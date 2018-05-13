#include "stacks.h"

Stack *stk_create()
{
    Stack *p = malloc(sizeof(Stack));
    p->top = NULL;
    p->heigh = 0;
    return p;
}

Stack *stk_push(Stack *p, seed_region *s)
{
    SItem *new = malloc(sizeof(SItem));
    new->under = p->top;
    p->top = new;
    new->region = s;
    p->heigh++;
    return new;
}

seed_region *stk_pop(Stack *p)
{
    if (!p->heigh)
        return NULL;
    SItem *drop = p->top;
    seed_region *item = drop->region;
    p->top = p->top->under;
    p->heigh--;
    // free(drop);
    return item;
}