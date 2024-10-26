#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <kos.h>

#include "s_video.h"
#include "s_input.h"
#include "s_mobj.h"


void A_PlayerMove(mobj_t* player)
{
	static uint8_t cooldown_value = 5;
	static uint8_t bullet_cooldown = 0;
	
	//Get input stats
	input_t input = INPUT_GetInputState();

	float player_speed = input.dec ? 2.0f : 4.0f;

	if (bullet_cooldown) bullet_cooldown--;
	
	if (input.shoot)
	{
		if (!bullet_cooldown)
		{
			A_PlayerShoot(player);
			bullet_cooldown = cooldown_value;
		}
	}
	
	//Don't let player move if it's out boundary
	if ((uint16_t)player->x+player->radius+player->speed >= GSCR_WIDTH+32)
	{
		player->x -= player->speed;
		player->speed = 0;
		return;
	}
	else if ((uint16_t)player->x-player->radius-player->speed <= GSCR_X)
	{
		player->x += player->speed;
		player->speed = 0;
		return;
	}
	if ((uint16_t)player->y+player->radius+player->speed >= GSCR_HEIGHT)
	{
		player->y -= player->speed;
		player->speed = 0;
		return;
	}
	else if ((uint16_t)player->y-player->radius-player->speed <= GSCR_Y+16)
	{
		player->y += player->speed;
		player->speed = 0;
		return;
	}
	
	if (input.up) 
	{
		player->speed = player_speed; 
		
		if (input.right)
			player->angle = 135;
		else if (input.left)
			player->angle = 225;
		else
			player->angle = 180;
	}
	if (input.down) 
	{
		player->speed = player_speed; 
		
		if (input.right)
			player->angle = 45;
		else if (input.left)
			player->angle = 315;
		else
			player->angle = 0;
	}
	if (input.left) 
	{
		player->speed = player_speed; 
	
		if (input.up)
			player->angle = 225;
		else if (input.down)
			player->angle = 315;
		else
			player->angle = 270;
	}
	if (input.right) 
	{
		player->speed = player_speed; 
		
		if (input.up)
			player->angle = 135;
		else if (input.down)
			player->angle = 45;
		else
			player->angle = 90;
	}
	
	if (!input.up && !input.down
		&& !input.left && !input.right)
		player->speed = 0;
}

void A_PlayerShoot(mobj_t* player)
{
	mobj_t* bullet;
	bullet = MOBJ_Create(MT_RBULLET, player->x, player->y, 180);
	bullet->speed = 8.0f;
}