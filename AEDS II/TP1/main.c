#include <stdio.h>
#include <stdlib.h>

#include "netpbm.h"

unsigned int getThreshold(char *path);

int main(int argc, char **argv)
{
    PBM_FILE input = pbm_read_file(argv[1]);
    unsigned int threshold = getThreshold(argv[1]);
    return 0;
}

unsigned int getThreshold(char *path)
{
    FILE *pFile = fopen(path, "r");
    int unsigned threshold;
    char str[3];
    fscanf(pFile, "%s", str);
    fscanf(pFile, "%u", &threshold);
    fclose(pFile);
}