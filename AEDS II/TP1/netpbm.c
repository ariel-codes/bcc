#include "netpbm.h"

PBM_FILE pbm_read_file(char *path)
{
    FILE *pFile = fopen(path, "r");
    if (pFile == NULL)
        exit(42);
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
    fscanf(pFile, "%u %u", &file.resolution_x, &file.resolution_y);
    fscanf(pFile, "%u", &file.depth);

    long pix_number = file.resolution_x * file.resolution_y;
    file.content.bw = malloc(sizeof(char) * pix_number);

    for (int i = 0; i < pix_number; i++)
    {
        fscanf(pFile, "%hhu", &file.content.bw[i]);
    }

    fclose(pFile);

    return file;
}

AUX_FILE pbm_getauxf(char *path)
{
    FILE *aFile = fopen(path, "r");
    if (aFile == NULL)
        exit(-1);
    AUX_FILE aux;
    fscanf(aFile, "%hhu", &aux.seed_n);
    fscanf(aFile, "%hhu", &aux.threshold);

    Stack *s = stk_create();
    for (int i = 0; i < aux.seed_n; i++)
    {
        seed_region *region = malloc(sizeof(seed_region));
        fscanf(aFile, "%lu,%lu <%hhu,%hhu,%hhu>", &region->x, &region->y, &region->r, &region->g, &region->b);
        stk_push(s, region);
    }
    aux.seed_stack = s;

    fclose(aFile);
    return aux;
}

void pbm_write_file(PBM_FILE file)
{
    FILE *out = fopen(file.filename, "w");
    fprintf(out, "P3\n%lu %lu\n%hhu\n", file.resolution_x, file.resolution_y, file.depth);
    int length = file.resolution_x * file.resolution_y;
    switch (file.encoding)
    {
    case P3:
        for (long i = 0; i < length; i++)
        {
            unsigned char *pix = file.content.rgb + 3 * i;
            fprintf(out, "%u %u %u\n", pix[0], pix[1], pix[2]);
        }
        break;
    default:
        break;
    }
    fclose(out);
}