#ifndef __S_MOBJ_H__
#define __S_MOBJ_H__

#include "s_state.h"

//The mobj system is Doom-based

typedef enum
{
	MT_NONE=0,
	MT_REIMU,
	//MT_MARISA,
	//MT_SANAE,
	MT_BFAIRY,
	MT_RBULLET,
	MT_BBULLET,
	NUM_MOBJS
} mobj_num_t;

//It will be used to decide initial values to a new mobj
typedef struct
{
	mobj_num_t type;
	int16_t hp;
	state_num_t state;
	uint8_t radius;
	uint8_t flags;
} mobj_model_t;

typedef struct mobj_s
{
	uint8_t type;
	int16_t hp;
	float x;
	float y;
	float speed;
	uint8_t radius;
	uint16_t angle;
	state_t state;
	uint8_t flags;
	
	struct mobj_s* next;
	struct mobj_s* prev;
} mobj_t;

mobj_t* MOBJ_GetFirstMobj();
mobj_t* MOBJ_GetLastMobj();
mobj_t* MOBJ_Create(uint8_t type, uint16_t x, uint16_t y, uint16_t angle);
void MOBJ_Remove(mobj_t** mobj);
void MOBJ_ClearList();
void MOBJ_Update();
void MOBJ_ChangeState(mobj_t* mobj, state_num_t state);
uint8_t MOBJ_CheckCollision(mobj_t* mo1, mobj_t* mo2);

//Actions
void A_PlayerMove(mobj_t* player);
void A_PlayerShoot(mobj_t* player);

void A_BFairyMove(mobj_t* bfairy);

#endif