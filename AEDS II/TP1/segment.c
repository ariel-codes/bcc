#include "segment.h"

#include <stdio.h>
#include <stdlib.h>
#include "stacks.h"

#define SEED_X 0
#define SEED_Y 0

Stack *seg_generate(PBM_FILE image, unsigned int threshold)
{
    unsigned char **space = &(image.content);
    _Bool **metadata = &(image.metadata);
    Queue *to_add = qeu_create();
    qeu_insert(to_add, space[SEED_X][SEED_Y]);
    while (to_add->head != NULL)
    {
        Pixel p = qeu_deque(to_add);
        if(metadata[p.x][p.y])
            continue;
        // Sul
        if (p.y + 1 < image.resolution_y && abs(space[p.x][p.y] - space[p.x][p.y + 1]) <= threshold)
            qeu_insert(to_add, space[p.x][p.y + 1]);
        // Norte
        if (p.y - 1 >= 0 && abs(space[p.x][p.y] - space[p.x][p.y - 1]) <= threshold)
            qeu_insert(to_add, space[p.x][p.y + 1]);
        // Leste
        if (p.x + 1 < image.resolution_x && abs(space[p.x][p.y] - space[p.x + 1][p.y]) <= threshold)
            qeu_insert(to_add, space[p.x][p.y + 1]);
        // Oeste
        if (p.x - 1 >= 0 && abs(space[p.x][p.y] - space[p.x - 1][p.y]) <= threshold)
            qeu_insert(to_add, space[p.x][p.y + 1]);
    }
}

Queue *seg_grow(unsigned char *space, unsigned x, unsigned y)
{
}
