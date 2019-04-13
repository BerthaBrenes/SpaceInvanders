#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#include <stdbool.h>

#include "SDL.h"
#include"SDL_image.h"

#include "defs.h"
#include "structs.h"

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

#undef main
