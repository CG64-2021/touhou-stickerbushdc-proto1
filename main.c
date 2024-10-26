#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kos.h>

#include "m_utils.h"
#include "s_dataLoader.h"
#include "s_input.h"
#include "s_video.h"
#include "s_mobj.h"

#define TARGET_FPS 60
#define FRAME_TIME (1000/TARGET_FPS)


int main(int argc, char** argv)
{
	DATA_Init(); //Init filesystem
	INPUT_LoadDefaultValues(); //Init input
	VID_Init(); //Init rendering
	
	//TODO: botar pra carregar os sprites necessários no cache a depender do gamestate 
	SPR_LoadSpriteToCache(SPR_BSKY00, "/cd/spr_bsky00.bin", NULL);
	SPR_LoadSpriteToCache(SPR_REIMUIDLE00, "/cd/spr_reimu00.bin", "/cd/spr_reimu00.msk"); //load player sprite and mask in the spr_cache
	SPR_LoadSpriteToCache(SPR_REIMUIDLE01, "/cd/spr_reimu01.bin", "/cd/spr_reimu01.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE02, "/cd/spr_reimu02.bin", "/cd/spr_reimu02.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE03, "/cd/spr_reimu03.bin", "/cd/spr_reimu03.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE04, "/cd/spr_reimu04.bin", "/cd/spr_reimu04.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE05, "/cd/spr_reimu05.bin", "/cd/spr_reimu05.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE06, "/cd/spr_reimu06.bin", "/cd/spr_reimu06.msk");
	SPR_LoadSpriteToCache(SPR_REIMUIDLE07, "/cd/spr_reimu07.bin", "/cd/spr_reimu07.msk");
	SPR_LoadSpriteToCache(SPR_BFAIRY00, "/cd/spr_bfairy00.bin", "/cd/spr_bfairy00.msk");
	SPR_LoadSpriteToCache(SPR_RBULLET, "/cd/spr_rbullet.bin", "/cd/spr_rbullet.msk");
	SPR_LoadSpriteToCache(SPR_BBULLET, "/cd/spr_bbullet.bin", "/cd/spr_bbullet.msk");
	
	
	//Create player
	MOBJ_Create(MT_REIMU, 320, 224, 0);
	
	//Create fairy
	MOBJ_Create(MT_BFAIRY, 208, 100, 45);
	
	//FPS
	uint64_t start_time;
	uint64_t end_time; 
	uint64_t delta_time;
	
	while(1)
	{
		start_time = timer_ms_gettime64();
		
		INPUT_Update();
		MOBJ_Update();
		VID_Update();
		
		end_time = timer_ms_gettime64();
		delta_time = end_time - start_time;
		//Limit to 60FPS
		if (delta_time < FRAME_TIME)
		{
			thd_sleep(FRAME_TIME - delta_time);
		}
	}
	
	DATA_Close();
	
	return 0;
}