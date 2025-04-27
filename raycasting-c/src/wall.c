#include "wall.h"

// Change the color intensity based on a factor value between 0 and 1
void changeColorIntensity(color_t* color, float factor) {
    color_t a = (*color & 0xFF000000);
    color_t r = (*color & 0x00FF0000) * factor;
    color_t g = (*color & 0x0000FF00) * factor;
    color_t b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void renderWallProjection(void) {
    for (int x = 0; x < NUM_RAYS; x++) {
        // Calculate the perpendicular distance to avoid the fish-eye distortion
        float perpDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
        
        // Calculate the projected wall height
        float wallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        // Find the wall top Y value
        int wallTopY = (WINDOW_HEIGHT / 2) - (wallHeight / 2);
        wallTopY = wallTopY < 0 ? 0 : wallTopY;

        // Find the wall bottom Y value
        int wallBottomY = (WINDOW_HEIGHT / 2) + (wallHeight / 2);
        wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;

        // Draw the ceiling
        for (int y = 0; y < wallTopY; y++) {
            drawPixel(x, y, 0xFF444444);
        }

        // Draw the textured wall
        int textureOffsetX;
        if (rays[x].wasHitVertical)
            textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
        else
            textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;

        // Get the correct texture id number from the map content
        int texNum = rays[x].wallHitContent - 1;

        // Query the texture width and height from the upng
        int textureWidth = upng_get_width(textures[texNum]);
        int textureHeight = upng_get_height(textures[texNum]);

        // Render the wall from wallTopY to wallBottomY
        for (int y = wallTopY; y < wallBottomY; y++) {
            int distanceFromTop = y + (wallHeight / 2) - (WINDOW_HEIGHT / 2);
            int textureOffsetY = distanceFromTop * ((float)textureHeight / wallHeight);

            // Set the color of the wall based on the color from the texture
            color_t* wallTextureBuffer = (color_t*) upng_get_buffer(textures[texNum]);
            color_t texelColor = wallTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];

            // Make the pixel color darker if the ray hit was vertical
            if (rays[x].wasHitVertical) {
                changeColorIntensity(&texelColor, 0.7);
            }

            drawPixel(x, y, texelColor);
        }

        // Draw the floor
        for (int y = wallBottomY; y < WINDOW_HEIGHT; y++) {
            drawPixel(x, y, 0xFF888888);
        }
    }
}
