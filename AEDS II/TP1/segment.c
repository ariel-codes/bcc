#include "segment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacks.h"

void seg_generate(PBM_FILE image, AUX_FILE settings)
{
    unsigned char *map = calloc(image.resolution_x * image.resolution_y, sizeof(char));
    unsigned char *segmented = calloc(image.resolution_x * image.resolution_y * 3, sizeof(char));

    Stack *s = settings.seed_stack;
    PBM_FILE newfile;
    newfile.resolution_x = image.resolution_x;
    newfile.resolution_y = image.resolution_y;
    newfile.encoding = P3;
    newfile.filename = "out.ppm";
    newfile.depth = 255;
    newfile.content.rgb = segmented;

    while (s->heigh > 0)
    {
        seed_region *region = stk_pop(s);
        region->original = &image;
        region->projection = &newfile;
        seg_grow(region->x, region->y, region, map, settings.threshold);
    }
    pbm_write_file(newfile);
}

int seg_grow(long x, long y, seed_region *reg, unsigned char *map, const t)
{
    const long rX = reg->original->resolution_x, rY = reg->original->resolution_y;
    // Cima, direita, esquerda, baixo, meio (pixel atual)
    long indexes[] = {
        x + rX * (y - 1),
        (x + 1) + rX * y,
        (x - 1) + rX * y,
        x + rX * (y + 1),
        x + rX * y};

    unsigned char colors[] = {reg->r, reg->g, reg->b};
    memcpy(reg->projection->content.rgb + indexes[4] * 3, colors, sizeof(char) * 3);
    map[indexes[4]] = 1;

    for (int i = 0; i < 4; i++)
    {
        if (map[indexes[i]] == 0 && abs(reg->original->content.bw[indexes[i]] - reg->original->content.bw[indexes[4]]) <= t)
        {
            switch (i)
            {
            case 0:
                if (x >= 0 && y - 1 >= 0 && x < rX && y - 1 < rY)
                    seg_grow(x, y - 1, reg, map, t);
                break;
            case 1:
                if (x + 1 >= 0 && y >= 0 && x + 1 < rX && y < rY)
                    seg_grow(x + 1, y, reg, map, t);
                break;
            case 2:
                if (x - 1 >= 0 && y >= 0 && x - 1 < rX && y < rY)
                    seg_grow(x - 1, y, reg, map, t);
                break;
            case 3:
                if (x >= 0 && y + 1 >= 0 && x < rX && y + 1 < rY)
                    seg_grow(x, y + 1, reg, map, t);
                break;
            }
        }
    }
}
