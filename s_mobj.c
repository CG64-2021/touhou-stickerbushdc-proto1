#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <kos.h>

#include "m_utils.h"
#include "s_video.h"
#include "s_mobj.h"

static uint16_t num_mobjs = 0;

//List of mobjs available
static mobj_model_t mobj_models[NUM_MOBJS] = {
	{MT_NONE, 0, S_NONE, 0, 0x0},
	{MT_REIMU, 1, S_REIMUIDLE00, 4, 0x1},
	{MT_BFAIRY, 100, S_BFAIRY00, 14, 0x1},
	{MT_RBULLET, 1, S_RBULLET, 10, 0x1},
	{MT_BBULLET, 1, S_BBULLET, 10, 0x1}
};


static mobj_t* head = NULL;
static mobj_t* tail = NULL;

mobj_t* MOBJ_GetFirstMobj()
{
	return head;
}

mobj_t* MOBJ_GetLastMobj()
{
	return tail ? tail : head;
}

static void MOBJ_PutinTheList(mobj_t* mobj)
{
	if (!head) //If the list is empty
	{
		mobj->prev = NULL;
		mobj->next = NULL;
		head = mobj;
		tail = mobj;
		num_mobjs++;
		return;
	}
	
	tail->next = mobj;
	mobj->prev = tail;
	mobj->next = NULL;
	tail = mobj;
	num_mobjs++;
	
}

mobj_t* MOBJ_Create(uint8_t type, uint16_t x, uint16_t y, uint16_t angle)
{
	mobj_t* mo = (mobj_t*)malloc(sizeof(mobj_t));
	if (!mo) return NULL;
	memset(mo, 0, sizeof(mobj_t));
	
	mo->type = type;
	mo->hp = mobj_models[type].hp;
	mo->x = (float)x; 
	mo->y = (float)y;
	mo->radius = mobj_models[type].radius;
	mo->angle = angle;
	ST_GetStateFromList(&mo->state, mobj_models[type].state);
	mo->flags = mobj_models[type].flags;
	
	MOBJ_PutinTheList(mo);
	
	return mo;
}

static void MOBJ_RemoveFromList(mobj_t* mobj)
{
	if (!mobj) return;
	mobj_t* prev = mobj->prev;
	mobj_t* next = mobj->next;
	
	if(prev) prev->next = next;
	if(next) next->prev = prev;
}

void MOBJ_Remove(mobj_t** mobj)
{
    if (!mobj || !*mobj) return;

    if (*mobj == head)
    {
        head = head->next;
        if (head) head->prev = NULL;
    }
    
    else if (*mobj == tail)
    {
        tail = tail->prev;
        if (tail) tail->next = NULL;
    }
    else
    {
        MOBJ_RemoveFromList(*mobj);
    }

    free(*mobj);
    *mobj = NULL;
    num_mobjs--;
}

void MOBJ_ClearList()
{
	mobj_t* mo;
	while(head)
	{
		mo = tail;
		tail = tail->prev;
		free(mo);
	}
	head = NULL;
	tail = NULL;
}

void MOBJ_Update()
{
	mobj_t* aux = head;
	while(aux)
	{
		//Check if a mobj is outside the screen
		if (aux->x < 0 || aux->x > SCREEN_WIDTH || aux->y < 0 || aux->y > SCREEN_HEIGHT)
		{
			aux->speed = 0;
			mobj_t* aux2 = aux;
			aux = aux->next;
			MOBJ_Remove(&aux2);
			continue;
		}
		
		//Update state
		ST_UpdateState(&aux->state);
		
		//Exec action functions
		if (aux->state.actionf.acp1)
		{
			aux->state.actionf.acp1(aux);
		}
		
		//Update X, Y positions
		aux->x += SIN(aux->angle)*aux->speed;
		aux->y += COS(aux->angle)*aux->speed;
		
		aux = aux->next;
	}
}

void MOBJ_ChangeState(mobj_t* mobj, state_num_t state)
{
	ST_GetStateFromList(&mobj->state, state);
}

uint8_t MOBJ_CheckCollision(mobj_t* mo1, mobj_t* mo2)
{
	uint16_t left1 = (uint16_t)(mo1->x - mo1->radius);
	uint16_t right1 = (uint16_t)(mo1->x + mo1->radius);
	uint16_t top1 = (uint16_t)(mo1->y - mo1->radius);
	uint16_t bottom1 = (uint16_t)(mo1->y + mo1->radius);
	
	uint16_t left2 = (uint16_t)(mo2->x - mo1->radius);
	uint16_t right2 = (uint16_t)(mo2->x + mo1->radius);
	uint16_t top2 = (uint16_t)(mo2->y - mo1->radius);
	uint16_t bottom2 = (uint16_t)(mo2->y + mo1->radius);
	
	if (left1 == right2 && bottom1 == top2)
		return 1;
	if (left2 == right1 && bottom2 == top1)
		return 1;
	
	return 0;
}