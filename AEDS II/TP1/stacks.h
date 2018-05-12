#pragma once

#include "queues.h"

typedef struct _s_item
{
    Queue *region;
    struct _s_item *under;
} SItem;

typedef struct _stack
{
    SItem *top;
    int heigh;
} Stack;

Stack *stk_create();

SItem *stk_push(Stack *p, Queue *l);

Queue *stk_pop(Stack *p);