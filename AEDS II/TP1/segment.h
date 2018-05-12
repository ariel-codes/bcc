#pragma once

#include "netpbm.h"
#include "stacks.h"

Stack *seg_generate(PBM_FILE image, unsigned int threshold);

