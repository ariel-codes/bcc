#pragma once

#include <stdlib.h>

typedef enum
{
    P2,
    P3
} encoding_type;

typedef union _content {
    unsigned char *bw;
    unsigned char *rgb;
} img;

typedef struct _pbm_file
{
    char *filename;
    encoding_type encoding;
    unsigned char depth;
    size_t resolution_x;
    size_t resolution_y;
    img content;
} PBM_FILE;

typedef struct _regions
{
    unsigned char r, g, b;
    size_t x, y;
    PBM_FILE *original;
    PBM_FILE *projection;
} seed_region;

typedef struct _s_item
{
    seed_region *region;
    struct _s_item *under;
} SItem;

typedef struct _stack
{
    SItem *top;
    int heigh;
} Stack;

typedef struct _aux_file
{
    unsigned char seed_n;
    unsigned char threshold;
    Stack *seed_stack;
} AUX_FILE;



