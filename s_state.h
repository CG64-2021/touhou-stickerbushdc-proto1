#ifndef __S_STATE_H__
#define __S_STATE_H__

#include "s_sprCache.h"

typedef void (*actionf_v)();
typedef void (*actionf_p1)(void*);
typedef void (*actionf_p2)(void*, void*);

typedef union
{
	actionf_p1 acp1;
	actionf_v acv;
	actionf_p2 acp2;
} actionf_t;


typedef enum
{
	S_NONE=0,
	S_REIMUIDLE00,
	S_REIMUIDLE01,
	S_REIMUIDLE02,
	S_REIMUIDLE03,
	S_REIMUIDLE04,
	S_REIMUIDLE05,
	S_REIMUIDLE06,
	S_REIMUIDLE07,
	S_BFAIRY00,
	S_RBULLET,
	S_BBULLET,
	NUM_STATES
} state_num_t;

typedef struct
{
	spr_id_t spr_num;
	int32_t duration;
	actionf_t actionf;
	state_num_t next_state;
} state_t;

void ST_GetStateFromList(state_t* in, state_num_t out);
void ST_UpdateState(state_t* state);

#endif