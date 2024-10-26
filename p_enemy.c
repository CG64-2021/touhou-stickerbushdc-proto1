#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kos.h>

#include "s_video.h"
#include "s_input.h"
#include "s_mobj.h"

#define BFAIRY_BULLET_COOLDOWN 5
//TODO: Fazer sistema de colisao circular talkei
//Acho que teremos que adicionar animacoes de morte tbm kk
void A_BFairyMove(mobj_t* bfairy)
{
	static uint8_t duration = BFAIRY_BULLET_COOLDOWN;
	static uint16_t angle = 0;
	mobj_t* bullets[8];
	
	angle++;
	
	if (!duration)
	{
		duration = BFAIRY_BULLET_COOLDOWN;
		bullets[0] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, angle); bullets[0]->speed = 4.0f;
		bullets[1] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+90)); bullets[1]->speed = 4.0f;
		bullets[2] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+180)); bullets[2]->speed = 4.0f;
		bullets[3] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+270)); bullets[3]->speed = 4.0f;
		bullets[4] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+45)); bullets[4]->speed = 4.0f;
		bullets[5] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+135)); bullets[5]->speed = 4.0f;
		bullets[6] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+225)); bullets[6]->speed = 4.0f;
		bullets[7] = MOBJ_Create(MT_BBULLET, bfairy->x, bfairy->y, (angle+315)); bullets[7]->speed = 4.0f;
	}
	duration--;
}