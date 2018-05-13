#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "stacks.h"

PBM_FILE pbm_read_file(char *path);

AUX_FILE pbm_getauxf(char *path);

void pbm_write_file(PBM_FILE file);
