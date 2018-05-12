#include <stdio.h>
#include <stdlib.h>

#include "netpbm.h"

PBM_FILE pbm_read_file(char *path)
{
    FILE *pFile = fopen(path, "r");
    PBM_FILE file;
    file.filename = path;
    char encode[3];
    fscanf(pFile, "%s", encode);
    switch (encode[1])
    {
    case '2':
        file.encoding = P2;
        break;
    case '3':
        file.encoding = P3;
        break;
    }
    fscanf(pFile, "%d %d", &file.resolution_x, &file.resolution_y);
    fscanf(pFile, "%d", &file.depth);

    int pix_number = file.resolution_x * file.resolution_y;
    file.content = (char *)malloc(sizeof(char) * pix_number);
    file.metadata = (char *)malloc(sizeof(_Bool) * pix_number);

    for (int i = 0; i < pix_number; i++)
    {
        int *intptr;
        fscanf(pFile, "%d", intptr);
        file.content[i] = (unsigned char)(*intptr);
        file.metadata[i] = 0;
    }

    fclose(pFile);

    return file;
}

// FILE *pbm_create_file(PBM_FILE file)
// {
// }