#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <kos.h>
#include <dc/maple.h>
#include <dc/maple/controller.h>

#include "s_input.h"

static input_t input;

//Values
static int up;
static int down;
static int left;
static int right;
static int start;
static int shoot;
static int bomb;
static int dec;


//TODO: Criar módulo de save na VMU para salvar configs de input
//Caso nao tiver, carregue valores padrao
void INPUT_LoadDefaultValues()
{
	up = CONT_DPAD_UP;
	down = CONT_DPAD_DOWN;
	left = CONT_DPAD_LEFT;
	right = CONT_DPAD_RIGHT;
	start = CONT_START;
	shoot = CONT_A;
	bomb = CONT_B;
	dec = CONT_X;
}

void INPUT_Update()
{
	maple_device_t* dev;
	cont_state_t* state;
	
	dev = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
	if (!dev) return;
	
	state = (cont_state_t*)maple_dev_status(dev);
	if (!state) return;
	
	//Reset before getting updates
	input.buttons = 0x00;
	
	if (state->buttons & up) input.up = 1;
	if (state->buttons & down) input.down = 1;
	if (state->buttons & left) input.left = 1;
	if (state->buttons & right) input.right = 1;
	if (state->buttons & start) input.start = 1;
	if (state->buttons & shoot) input.shoot = 1;
	if (state->buttons & bomb) input.bomb = 1;
	if (state->buttons & dec) input.dec = 1;
}

input_t INPUT_GetInputState()
{
	return input;
}