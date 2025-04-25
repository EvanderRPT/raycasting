#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdint.h>
#include "defs.h"
#include "upng.h"

typedef struct {
    int width;
    int height;
    uint32_t* texture_buffer;
    upng_t* upngTexture;
} texture_t;

extern texture_t wallTextures[NUM_TEXTURES];

void loadWallTextures(void);
void freeWallTextures(void);

#endif
