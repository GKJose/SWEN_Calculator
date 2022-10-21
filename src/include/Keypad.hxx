#ifndef KEYPAD_H
#define KEYPAD_H
#include <calc_conf.h>

#if ENABLE_MCP_KEYPAD
#include <lvgl/lvgl.h>
#include <MCP23017.hxx>
LV_EVENT_KEY_PRESSED = lv_event_register_id();
class Keypad
{
public:
	Keypad();
	~Keypad();
	 void poll();
	 bool isPressed(uint8_t id);
	 bool isBothPressed(uint8_t id1,uint8_t id2);
	 void reset();
	
private:
	MCP23017 mcp;
	uint64_t buttonStates;
	const int cols[5] = {0,1,2,3,4};
	const int rows[7] = {8,9,10,11,12,13,14};

};

//Begin MCP definitions
#define ADDRESS 0x27
#define BUS 1
#define N_ROWS 7
#define N_COLS 5




//Begin button defines

//COLUMN ONE
#define x_BUTTON 0
#define A_BUTTON  1
#define B_BUTTON 2
#define C_BUTTON  3
#define D_BUTTON 4
#define E_BUTTON 5
#define F_BUTTON 6

//COLUMN TWO
#define HOME_BUTTON 8
#define LEFT_BUTTON 9
#define SETTINGS_BUTTON 10
#define SEVEN_BUTTON 11
#define FOUR_BUTTON 12
#define ONE_BUTTON 13
#define b_BUTTON 14
//COLUMN THREE
#define UP_BUTTON 16
#define COMMA_BUTTON 17
#define DOWN_BUTTON 18
#define EIGHT_BUTTON 19
#define FIVE_BUTTON 20
#define TWO_BUTTON 21
#define ZERO_BUTTON 22
//COLUMN FOUR
#define RESET_BUTTON 24
#define RIGHT_BUTTON 25
#define LEFT_BRACKET_BUTTON 26
#define NINE_BUTTON 27
#define SIX_BUTTON 28
#define THREE_BUTTON 29
#define DOT_SIGN_BUTTON 30
//COLUMN FIVE
#define CLEAR_BUTTON 32
#define DELETE_BUTTON 33 
#define RIGHT_BRACKET_BUTTON 34
#define MULTIPLY_BUTTON 35
#define SUBTRACT_BUTTON 36 
#define ADD_BUTTON 37
#define ENTER_BUTTON 38

#endif
#endif
