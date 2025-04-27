#ifndef SPRITE_H
#define SPRITE_H

#include "defs.h"
#include "graphics.h"
#include "player.h"
#include "texture.h"

typedef struct {
    float x;
    float y;
    float distance;
    float angle;
    bool visible;
    int texture;
} sprite_t;

void renderMapSprites(void);
void renderSpriteProjection(void);

#endif
