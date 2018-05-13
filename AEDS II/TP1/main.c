#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "netpbm.h"
#include "segment.h"

unsigned int getThreshold(char *path);

int main(int argc, char **argv)
{
    PBM_FILE input = pbm_read_file(argv[1]);
    int namesize = strlen(input.filename);
    char *aux = malloc(sizeof(char) * namesize);
    strcpy(aux, input.filename);
    aux[namesize - 3] = 't';
    aux[namesize - 2] = 'x';
    aux[namesize - 1] = 't';

    AUX_FILE settings = pbm_getauxf(aux);
    seg_generate(input, settings);
    return 0;
}
