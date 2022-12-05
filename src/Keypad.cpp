//Keypad.cpp
//************************************************************
//*                                                          
//* Author: Mendez, Jose - Cyberbits01
//*`Purpose: The class representing the keypad interface, stores button states.
//*
//* Contains:                                        |UPDATE
//* Keypad (Constructor)
//* ~Keypad (Deconstructor)
//*	poll
//* isPressed
//* isBothPressed
//* reset
//*
//* Date: 16Nov22
//************************************************************

#include <Keypad.hxx>

#if ENABLE_MCP_KEYPAD
uint32_t LV_EVENT_KEY_PRESSED = lv_event_register_id();
Keypad::Keypad(){
	// Create the MCP23017 driver.
	mcp = MCP23017(BUS,ADDRESS);
	//Set the button states to zero.
	buttonStates = 0;	
	//Open the I2C connection to the button matrix
	mcp.openI2C();
	
	//Initalize the MCP23017 pins
	for(int i = 0; i < N_COLS; i++){
	mcp.pinMode(cols[i],OUTPUT);
	}
	for(int i = 0; i < N_ROWS; i++){
	mcp.pinMode(rows[i],INPUT);
	}

	
}

Keypad::~Keypad(){
	//Close the I2C connection once this object is destoried.
	mcp.closeI2C();
}
//************************************************************
//* poll
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: To poll the keypad buttons via the MCP23017
//*
//* Usage: poll()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   digitalWrite							MCP23017.cpp
//*   readGPIO								MCP23017.CPP
//*   
//* Date: 16Nov22
//************************************************************
void Keypad::poll(){
        //Cycle through the columns, setting one column at a time to high
	for(int c = 0; c < N_COLS; c++){
		mcp.digitalWrite(cols[c],HIGH);
		uint64_t data = mcp.readGPIO(1);
		buttonStates |= data << 8*c;
		mcp.digitalWrite(cols[c],LOW);
		
	}

}
//************************************************************
//* isPressed
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: isPressed(id)
//*     id - The button id to check
//*     **MUST be called after poll **
//*
//* Returns: true if the button checked was pressed.
//*
//* Functions called:                   Source:
//*  
//*   
//* Date: 16Nov22
//************************************************************
bool Keypad::isPressed(uint8_t id){
	//Check if the bit associated with the button is set
	if(buttonStates & ( 1ULL << id)){
		//Set the button state to zero once we have processed it.
		buttonStates = buttonStates & ~(1ULL << id);
		return true;
	}
	return false;
}
//************************************************************
//* isBothPressed
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: isBothpressed(id1,id2)
//*     id1,id2 - The button id to check
//*
//* Returns: true if both were pressed.
//*
//* Functions called:                   Source:
//*   
//*   
//* Date: 16Nov22
//************************************************************
bool Keypad::isBothPressed(uint8_t id1,uint8_t id2){
	return ( buttonStates & ( 1ULL << id1) ) & ( buttonStates & ( 1ULL << id2) );
}
void Keypad::reset(){
	buttonStates = 0;
}

#endif
