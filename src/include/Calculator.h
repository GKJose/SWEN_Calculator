#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calc_conf.h"
#include <iostream>

#if ENABLE_MCP_KEYPAD
#include <Keypad.hxx>
#endif
#include <lvgl/lvgl.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <tabs.hxx>

#include <iostream>
#include <fstream>
#include <ctime>
#include <Util.h>

namespace Calculator{
    void createDemo();
	void update(lv_timer_t * timer);
    void main_screen_driver(lv_obj_t* parent);
	static void input_ta_event_handler(lv_event_t* e);
	static void output_ta_event_handler(lv_event_t* e);





	
}

#endif
