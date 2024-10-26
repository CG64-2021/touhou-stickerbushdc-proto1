#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kos.h>

#include "s_video.h"
#include "s_mobj.h"

static uint16_t __attribute__((aligned(32))) framebuffer[SCREEN_SIZE];

void VID_Init()
{
	//Init video system
	vid_init(DM_640x480_NTSC_IL, PM_RGB565);
}


void VID_FillScreen(uint16_t* screen, uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t color = (uint16_t)PACK_PIXEL(r, g, b);
	
	sq_set16(screen, color, SCREEN_RSIZE);
}

void VID_DrawPixel(uint16_t* screen, int16_t x, int16_t y, uint16_t color)
{
	screen[y*SCREEN_WIDTH+x] = color;
}

void VID_DrawBackground(uint16_t* screen, sprite_t* sprite, int16_t yoffset)
{
	uint16_t* scr_index;
	uint16_t* spr_index;
	
	uint16_t* spr_data = sprite->spr_data.data;
	uint16_t spr_w = sprite->w;
	uint16_t spr_h = sprite->h;
	
	uint16_t x = GSCR_X;
	uint16_t y = GSCR_Y;
	
	uint16_t i;
	for(i=0; i < GSCR_HEIGHT; ++i)
	{
		scr_index = &screen[(y+i)*SCREEN_WIDTH+x];
		spr_index = &spr_data[(i+yoffset)%spr_h*spr_w];
		sq_cpy(scr_index, spr_index, spr_w*2);
		sq_cpy(scr_index+spr_w, spr_index, (GSCR_WIDTH-spr_w)*2); //if a sprite width < GSCR_WIDTH, render the rest
	}
}

void VID_FastDrawSprite(uint16_t* screen, sprite_t* sprite, int16_t x, int16_t y)
{
	if (x < GSCR_X || y < GSCR_Y || x + sprite->w > GSCR_WIDTH || y + sprite->h > GSCR_HEIGHT) 
        return;

	uint16_t* scr_index;
	uint16_t* spr_index;
	
	uint16_t* spr_data = sprite->spr_data.data;
	uint16_t spr_w = sprite->w;
	uint16_t spr_h = sprite->h;
	
	uint16_t i;
	for(i=0; i < spr_h; ++i)
	{
		scr_index = &screen[(y+i)*SCREEN_WIDTH+x];
		spr_index = &spr_data[i*spr_w];
		sq_cpy(scr_index, spr_index, spr_w*2);
	}
}

void VID_DrawSprite(uint16_t* screen, sprite_t* sprite, int16_t x, int16_t y)
{
	int32_t scr_index;
	uint32_t spr_index;
	uint8_t  msk_byte;
	uint8_t  msk_bit;
	
	uint16_t* spr_data = sprite->spr_data.data;
	uint8_t* spr_mask = sprite->spr_data.mask;
	
	if (!spr_data)
		return;
	if (x < GSCR_X || y < GSCR_Y || x + sprite->w > GSCR_WIDTH+32 || y + sprite->h > GSCR_HEIGHT+32) 
        return;
	
	uint16_t i, j;
	for(i=0; i < sprite->h; ++i)
	{
		scr_index = (y+i) * SCREEN_WIDTH + x;
		spr_index = i * sprite->w;
		
		for(j=0; j < sprite->w; ++j)
		{
			
			if (spr_mask)
			{
				msk_byte = spr_mask[(spr_index+j)/8];
				msk_bit = 1 << (7 - ((spr_index+j)%8)); 

				if (!(msk_byte & msk_bit)) continue;
			}
			
			screen[scr_index + j] = spr_data[spr_index + j];
		}
	}
}

void VID_Update()
{
	VID_FillScreen(framebuffer, 0, 0xFF, 0); //Clear framebuffer

	//Render y-scrolling background
	static uint8_t yoffset = 0;
	static uint8_t timer = 5;	
	if (timer-- <= 0)
	{
		yoffset++;
		timer = 5;
	}
	VID_DrawBackground(framebuffer, &spr_list[SPR_BSKY00], yoffset);
	
	//Render all existing mobjs
	sprite_t* sprite;
	mobj_t* mo = MOBJ_GetFirstMobj();
	while (mo)
	{
		sprite = &spr_list[mo->state.spr_num];
		if (sprite->spr_data.mask)
			VID_DrawSprite(framebuffer, sprite, mo->x-sprite->w/2, mo->y-sprite->h/2);
		else
			VID_FastDrawSprite(framebuffer, sprite, mo->x-sprite->w/2, mo->y-sprite->h/2);
		
		mo = mo->next;
	}
	
	memcpy(vram_s, framebuffer, SCREEN_RSIZE); //Update VRAM to render the fb on screen
}