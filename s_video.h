#ifndef __S_VIDEO_H__
#define __S_VIDEO_H__

#include "s_sprCache.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GSCR_X 32
#define GSCR_Y 16
#define GSCR_WIDTH 384
#define GSCR_HEIGHT 448
#define SCREEN_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT)
#define SCREEN_RSIZE (SCREEN_SIZE*2)
#define PACK_PIXEL(r,g,b) (((r>>3)<<11) | ((g>>2)<<5) | ((b>>3)))

void VID_Init();
void VID_FillScreen(uint16_t* screen, uint8_t r, uint8_t g, uint8_t b);
void VID_DrawPixel(uint16_t* screen, int16_t x, int16_t y, uint16_t color);
void VID_DrawBackground(uint16_t* screen, sprite_t* sprite, int16_t yoffset);
void VID_DrawSprite(uint16_t* screen, sprite_t* sprite, int16_t x, int16_t y);
void VID_FastDrawSprite(uint16_t* screen, sprite_t* sprite, int16_t x, int16_t y);
void VID_Update();

#endif