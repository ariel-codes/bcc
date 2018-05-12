#include <stdlib.h>

#include "queues.h"

/*Funcoes de fila*/

Queue *qeu_create()
{
    Queue *l = malloc(sizeof(Queue));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/**
 * INSERE NO FIM 
 */
Queue *qeu_insert(Queue *l, unsigned char i[static 2])
{
    QItem *t = malloc(sizeof(QItem));
    t->behind = NULL;
    t->pix.x = i[0];
    t->pix.y = i[1];

    if (l->head == NULL)
    {
        l->head = t;
        l->tail = t;
    }
    l->tail->behind = t;
    l->tail = t;
    return l;
}

Queue *qeu_search(Queue *l, unsigned char v[static 2])
{
    QItem *i;
    for (i = l->head; i != NULL; i = i->behind)
    {
        if (i->pix.x == v[0] && i->pix.y == v[1])
            return i;
    }
    return NULL;
}

Pixel qeu_deque(Queue *l) /* Retira do início da fila */
{
    QItem *freeable = l->head;
    l->head = freeable->behind;
    Pixel p = freeable->pix;
    free(freeable);
    return p;
}

void qeu_free(Queue *l)
{
    QItem *p = l->head;
    while (p != NULL)
    {
        QItem *t = p->behind;
        free(p);
        p = t;
    }
    free(l);
}
