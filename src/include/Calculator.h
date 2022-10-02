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
#include <Number.h>
namespace Calculator{
    void createDemo();
	void update(lv_timer_t * timer);
	lv_obj_t* lv_textarea_input(lv_obj_t* parent);
    lv_obj_t* lv_textarea_output(lv_obj_t* parent);
    void main_screen_driver(lv_obj_t* parent, bool first_screen);
	lv_obj_t* lv_input_history_ta(lv_obj_t* parent, std::string output, lv_obj_t* active_ta);
	lv_obj_t* lv_result_ta(lv_obj_t* parent, std::string output, lv_obj_t* active_ta);	
	static void active_ta_event_handler(lv_event_t* e);
	static void clear_scr_btn_event_handler(lv_event_t* e);
	static void input_history_ta_event_handler(lv_event_t* e);




	
}

#endif
