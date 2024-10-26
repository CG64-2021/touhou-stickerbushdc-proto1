#ifndef __S_INPUT_H__
#define __S_INPUT_H__


typedef union
{
	uint8_t buttons;
	struct
	{
		uint8_t up : 1;
		uint8_t down : 1;
		uint8_t left : 1;
		uint8_t right : 1;
		uint8_t start : 1;
		uint8_t shoot : 1;
		uint8_t bomb : 1;
		uint8_t dec : 1; //deaccelerate
	};
} input_t;

void INPUT_LoadDefaultValues();
void INPUT_Update();
input_t INPUT_GetInputState();

#endif