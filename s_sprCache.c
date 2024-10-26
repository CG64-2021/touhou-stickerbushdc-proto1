#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kos.h>

#include "s_dataLoader.h"
#include "s_sprCache.h"

#define MAX_SPRITES 128

//You need to load sprites to cache so you can render them
static spr_data_t spr_cache[MAX_SPRITES];
static uint16_t spr_index = 0;

//List of sprite parameters
//spr_list[i].data is NULL because its data is in spr_cache
//So, you need to alloc the sprite data in spr_cache and use the ptr
//to point to an element of spr_cache array.
//This task is made by calling SPR_LoadSpriteToCache
sprite_t spr_list[NUM_SPRITES] = {
	{0, 0, {NULL, NULL}}, //SPR_NONE
	{256, 256, {NULL, NULL}}, //SPR_BSKY00
	{31, 45, {NULL, NULL}}, //SPR_REIMUIDLE00
	{31, 45, {NULL, NULL}}, //SPR_REIMUIDLE01
	{31, 46, {NULL, NULL}}, //SPR_REIMUIDLE02
	{31, 45, {NULL, NULL}}, //SPR_REIMUIDLE03
	{30, 46, {NULL, NULL}}, //SPR_REIMUIDLE04
	{31, 44, {NULL, NULL}}, //SPR_REIMUIDLE05
	{30, 44, {NULL, NULL}}, //SPR_REIMUIDLE06
	{31, 43, {NULL, NULL}}, //SPR_REIMUIDLE07
	{19, 22, {NULL, NULL}}, //SPR_BFAIRY00
	{12, 12, {NULL, NULL}}, //SPR_RBULLET
	{12, 12, {NULL, NULL}}  //SPR_BBULLET
};

//The game uses spr_list to render sprites in mobjs if, and only if, its data and mask are allocated
//If there's no mask, the sprite will be rendered with transparent pixels, otherwise transparent pixels won't be rendered
void SPR_LoadSpriteToCache(spr_id_t id, const char* spr_filename, const char* msk_filename)
{
	//Load new allocated sprite to cache
	if (spr_index >= MAX_SPRITES) return;
	
	spr_cache[spr_index].data = spr_filename ? (uint16_t*)DATA_GetFileData(spr_filename) : NULL;
	spr_cache[spr_index].mask = msk_filename ? DATA_GetFileData(msk_filename) : NULL;
	
	//Now we can render the allocated sprite
	spr_list[id].spr_data.data = spr_cache[spr_index].data;
	spr_list[id].spr_data.mask = spr_cache[spr_index].mask;
	
	//Update list index
	if (spr_cache[spr_index].data) spr_index++;
}

//Before loading sprites when initializing a stage, we need to clear the cache
void SPR_ClearSpriteCache()
{
	uint16_t i=0;
	while(i < MAX_SPRITES)
	{
		if (spr_cache[i].data) {free(spr_cache[i].data); spr_cache[i].data = NULL;}
		if (spr_cache[i].mask) {free(spr_cache[i].mask); spr_cache[i].mask = NULL;}
		i++;
	}
	spr_index = 0;
}