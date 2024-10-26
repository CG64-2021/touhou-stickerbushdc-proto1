#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "s_mobj.h"
#include "m_utils.h"

/*
typedef struct
{
	spr_id_t spr_num;
	int32_t duration;
	actionf_t action;
	state_num_t next_state;
} state_t;
*/
static state_t state_list[NUM_STATES] = {
	{SPR_NONE, -1, {NULL}, S_NONE},
	{SPR_REIMUIDLE00, 10, {A_PlayerMove}, S_REIMUIDLE01},
	{SPR_REIMUIDLE01, 10, {A_PlayerMove}, S_REIMUIDLE02},
	{SPR_REIMUIDLE02, 10, {A_PlayerMove}, S_REIMUIDLE03},
	{SPR_REIMUIDLE03, 10, {A_PlayerMove}, S_REIMUIDLE04},
	{SPR_REIMUIDLE04, 10, {A_PlayerMove}, S_REIMUIDLE05},
	{SPR_REIMUIDLE05, 10, {A_PlayerMove}, S_REIMUIDLE06},
	{SPR_REIMUIDLE06, 10, {A_PlayerMove}, S_REIMUIDLE07},
	{SPR_REIMUIDLE07, 10, {A_PlayerMove}, S_REIMUIDLE00},
	{SPR_BFAIRY00, -1, {A_BFairyMove}, S_BFAIRY00},
	{SPR_RBULLET, -1, {NULL}, S_RBULLET},
	{SPR_BBULLET, -1, {NULL}, S_BBULLET},
};	


void ST_GetStateFromList(state_t* in, state_num_t out)
{
	memcpy(in, &state_list[out], sizeof(state_t));
}

void ST_UpdateState(state_t* state)
{
	if (state->duration < 0) return;
	if (!state->duration)
	{
		state_num_t index = state->next_state;
		ST_GetStateFromList(state, index);
		return;
	}
	state->duration--;
	return;
}