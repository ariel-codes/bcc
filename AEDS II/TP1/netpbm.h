#pragma once

#include <stdio.h>

typedef enum
{
    P2,
    P3
} encoding_type;

typedef struct _pbm_file
{
    char *filename;
    encoding_type encoding;
    unsigned int depth;
    unsigned int resolution_x;
    unsigned int resolution_y;
    unsigned char *content;
    _Bool *metadata;
} PBM_FILE;

PBM_FILE pbm_read_file(char *path);

FILE *pbm_create_file(PBM_FILE file);