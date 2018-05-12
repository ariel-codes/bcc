#pragma once

typedef struct _pixel
{
    int x;
    int y;
} Pixel;

typedef struct _q_item
{
    Pixel pix;
    struct _item *behind;
} QItem;

typedef struct _queue
{
    QItem *head;
    QItem *tail;
} Queue;

/*Funcoes de Queue encadeada*/

Queue *qeu_create();

Queue *qeu_insert(Queue *l, unsigned char i[static 2]);

Queue *qeu_search(Queue *l, unsigned char v[static 2]);

Pixel qeu_deque(Queue *l);

void qeu_free(Queue *l);