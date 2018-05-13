#pragma once

#include <stdlib.h>
#include "netpbm.h"
#include "structures.h"

Stack *stk_create();

Stack *stk_push(Stack *p, seed_region *l);

seed_region *stk_pop(Stack *p);