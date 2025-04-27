#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdint.h>
#include "defs.h"
#include "upng.h"

#define NUM_TEXTURES 14

extern upng_t* textures[NUM_TEXTURES];

void loadTextures(void);
void freeTextures(void);

#endif
