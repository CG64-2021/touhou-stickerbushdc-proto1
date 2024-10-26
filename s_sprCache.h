#ifndef __S_SPRCACHE_H__
#define __S_SPRCACHE_H__

typedef enum
{
	SPR_NONE = 0,
	SPR_BSKY00,
	SPR_REIMUIDLE00,
	SPR_REIMUIDLE01,
	SPR_REIMUIDLE02,
	SPR_REIMUIDLE03,
	SPR_REIMUIDLE04,
	SPR_REIMUIDLE05,
	SPR_REIMUIDLE06,
	SPR_REIMUIDLE07,
	SPR_BFAIRY00,
	SPR_RBULLET,
	SPR_BBULLET,
	NUM_SPRITES
} spr_id_t;

typedef struct __attribute__((packed, aligned(4)))
{
	uint16_t* data; //16-bit sprite data
	uint8_t* mask; //1-bit mask data, it's used to check what pixels are transparent
} spr_data_t;

typedef struct
{
	uint16_t w;
	uint16_t h;
	spr_data_t spr_data;
} sprite_t;
extern sprite_t spr_list[NUM_SPRITES]; //Use this list to render sprites in other modules

void SPR_LoadSpriteToCache(spr_id_t id, const char* spr_filename, const char* msk_filename);
void SPR_ClearSpriteCache();

#endif