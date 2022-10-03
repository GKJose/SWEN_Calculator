#include <Calculator.h>
#include <ctime>
#include <string>
#include <sstream>
#include <unistd.h>
#if ENABLE_MCP_KEYPAD
#include <Keypad.hxx>
#endif

using namespace std;

/*Declarations*/
static lv_obj_t* textArea;
#if ENABLE_MCP_KEYPAD
static Keypad keypad;
#endif
/*Areas holds a list of pointers to the active text areas.
  (1 Input, 1 Output) = 1 Entry to the calculator.
  After 50 Entries the main screen clears to prevent memory overfill.
  Segmentation Fault occurs at 60 Entries, 120 Working Text areas.*/
lv_obj_t* areas[100];
int total;

static lv_obj_t* tabview;

void Calculator::createDemo(){
	tabview = lv_main_screen_tabs();
	textArea = areas[0];
}
void Calculator::update(lv_timer_t * timer){
	#if ENABLE_MCP_KEYPAD
	keypad.poll();
	if(keypad.isPressed(A_BUTTON)){
			lv_textarea_add_text(textArea,"A");
	}else if(keypad.isPressed(B_BUTTON)){
		lv_textarea_add_text(textArea,"B");
	}else if(keypad.isPressed(C_BUTTON)){
		lv_textarea_add_text(textArea,"C");
	}else if(keypad.isPressed(D_BUTTON)){
		lv_textarea_add_text(textArea,"D");
	}else if(keypad.isPressed(E_BUTTON)){
		lv_textarea_add_text(textArea,"E");
	}else if(keypad.isPressed(F_BUTTON)){
		lv_textarea_add_text(textArea,"F");		
	}
	else if(keypad.isPressed(SETTINGS_BUTTON)){
		lv_tabview_set_act(tabview,1,LV_ANIM_OFF);
	}else if(keypad.isPressed(HOME_BUTTON)){
		lv_tabview_set_act(tabview,0,LV_ANIM_OFF);
	}else if(keypad.isPressed(LEFT_BUTTON)){
		lv_textarea_cursor_left(textArea);
	}else if(keypad.isPressed(CONVERT_TO_DECIMAL_BUTTON)){

		std::string num = lv_textarea_get_text(textArea);
		std::string output;
		if(base == type::HEX){
			output = std::to_string(std::stoi(num,nullptr,16));
		}else if(base == type::BINARY){
			output = std::to_string(std::stoi(num,nullptr,2));
		}
		/*Create the new text areas*/
		lv_obj_t* parent = lv_obj_get_parent(textArea);
        Calculator::lv_input_history_ta(parent, num, textArea);
	    Calculator::lv_result_ta(parent, output, textArea);
        lv_obj_align(textArea, LV_ALIGN_BOTTOM_MID, 0, ( 35 * total) + 35);
        lv_textarea_set_text(textArea, "");
        lv_obj_scroll_to_view(textArea, LV_ANIM_OFF);

        lv_obj_scroll_by(parent, 0, 15, LV_ANIM_OFF);

	}else if(keypad.isPressed(SEVEN_BUTTON)){
		lv_textarea_add_text(textArea,"7");
	}else if(keypad.isPressed(FOUR_BUTTON)){
		lv_textarea_add_text(textArea,"4");
	}else if(keypad.isPressed(ONE_BUTTON)){
		lv_textarea_add_text(textArea,"1");
	}else if(keypad.isPressed(RESET_BUTTON)){
		lv_obj_t* parent = lv_obj_get_parent(textArea);
		lv_obj_clean(parent);
        Calculator::main_screen_driver(parent, false);
	}else if(keypad.isPressed(UP_BUTTON)){
		lv_obj_t* parent = lv_obj_get_parent(textArea);
		lv_obj_scroll_by(parent, 0, 25, LV_ANIM_OFF);
	}else if(keypad.isPressed(SELECT_BUTTON)){
		//Select
	}else if(keypad.isPressed(DOWN_BUTTON)){
		lv_obj_t* parent = lv_obj_get_parent(textArea);
		lv_obj_scroll_by(parent, 0, -25, LV_ANIM_OFF);
	}else if(keypad.isPressed(EIGHT_BUTTON)){
		lv_textarea_add_text(textArea,"8");
	}else if(keypad.isPressed(FIVE_BUTTON)){
		lv_textarea_add_text(textArea,"5");
	}else if(keypad.isPressed(TWO_BUTTON)){
		lv_textarea_add_text(textArea,"2");
	}else if(keypad.isPressed(ZERO_BUTTON)){
		lv_textarea_add_text(textArea,"0");
	}else if(keypad.isPressed(CONVERT_TO_SEM_BUTTON)){
		//Convert number to SEM
		//First,get type to determine course of action
		//Then, convert that base type into SEM
	}else if(keypad.isPressed(RIGHT_BUTTON)){
		lv_textarea_cursor_right(textArea);
	}else if(keypad.isPressed(CONVERT_TO_HEX_BUTTON)){

		//Convert number to HEX
		//First,get type to determine course of action
		//Then, convert that base type into HEX	
	}else if(keypad.isPressed(NINE_BUTTON)){
		lv_textarea_add_text(textArea,"9");
	}else if(keypad.isPressed(SIX_BUTTON)){
		lv_textarea_add_text(textArea,"6");
	}else if(keypad.isPressed(THREE_BUTTON)){
		lv_textarea_add_text(textArea,"3");
	}else if(keypad.isPressed(DOT_SIGN_BUTTON)){
		lv_textarea_add_text(textArea,".");
	}else if(keypad.isPressed(CLEAR_BUTTON)){
		lv_textarea_set_text(textArea,"");
	}else if(keypad.isPressed(DELETE_BUTTON)){
		lv_textarea_del_char(textArea);
	}else if(keypad.isPressed(DIVIDE_BUTTON)){
		lv_textarea_add_text(textArea,"/");
	}else if(keypad.isPressed(MULTIPLY_BUTTON)){
		lv_textarea_add_text(textArea,"*");
	}else if(keypad.isPressed(SUBTRACT_BUTTON)){
		lv_textarea_add_text(textArea,"-");
	}else if(keypad.isPressed(ADD_BUTTON)){
		lv_textarea_add_text(textArea,"+");
	}else if(keypad.isPressed(ENTER_BUTTON)){
		if(strcmp(lv_textarea_get_text(textArea),"") != 0)
			lv_event_send(textArea,LV_EVENT_READY,NULL);
	}	
	#endif
}
void Calculator::main_screen_driver(lv_obj_t* parent, bool first_screen)
{
    total = 0;

    /*Initial Input text area*/
    //lv_obj_t* active_ta = lv_active_ta(parent);
	
    lv_obj_t* active_ta = lv_textarea_create(parent);
	textArea = active_ta;
    areas[total] = active_ta;
    total++;
    lv_textarea_set_one_line(active_ta, true);
    lv_obj_set_width(active_ta, 320);
    lv_obj_align(active_ta, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_event_cb(active_ta, active_ta_event_handler, LV_EVENT_ALL,nullptr);
    lv_obj_add_state(active_ta, LV_STATE_FOCUSED);
	if(first_screen)
	{
		/*Create a button to toggle the keyboard*/
	
	}

    /*Put kb in view*/
    lv_obj_scroll_by(parent, 0, 25, LV_ANIM_OFF);

}

/*Callback functions*/
static void Calculator::active_ta_event_handler(lv_event_t* e)
{   
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* parent = lv_obj_get_parent(ta);
    if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
    {
        /*Focus on the clicked text area*/
		lv_obj_scroll_to_view(ta, LV_ANIM_OFF);
		lv_obj_scroll_by(parent, 0, 15, LV_ANIM_OFF);
    }
    else if (code == LV_EVENT_READY)
    {
        if(total > 60)
        {
        	lv_obj_clean(parent);
            Calculator::main_screen_driver(parent, false);
            return;
        }
		// Set the solution to the string output, the rest of the code handles displaying the result
        string output = "";
		
        const char *copy_input = lv_textarea_get_text(ta);
		
		if(isValidEquation(copy_input)){
			std::cout << "Equation is valid!";
			output = solveEquation(copy_input);
		}else{
			output = "ERROR: Invalid Equation.";
		}
        /*Create the new text areas*/
        Calculator::lv_input_history_ta(parent, copy_input, ta);
	    Calculator::lv_result_ta(parent, output, ta);
        lv_obj_align(ta, LV_ALIGN_BOTTOM_MID, 0, ( 35 * total) + 35);
        lv_textarea_set_text(ta, "");
        lv_obj_scroll_to_view(ta, LV_ANIM_OFF);

        lv_obj_scroll_by(parent, 0, 15, LV_ANIM_OFF);
    }

}

static void Calculator::input_history_ta_event_handler(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
	lv_obj_t* active_ta = static_cast<lv_obj_t*>(lv_event_get_user_data(e));

	if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
	{
		const char *copy_input = lv_textarea_get_text(ta);
		lv_textarea_set_text(active_ta, copy_input);
	}	
}



/*Graphical widget functions*/
lv_obj_t* Calculator::lv_input_history_ta(lv_obj_t* parent, std::string input, lv_obj_t* active_ta)
{
    lv_obj_t* ta = lv_textarea_create(parent);
    areas[total] = ta;
    total++;
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_width(ta, 320);
    lv_obj_align(ta, LV_ALIGN_BOTTOM_MID, 0, ( 35 * total));
    // Todo create dedicated eventhandler.
    lv_obj_add_state(ta, LV_STATE_DEFAULT);
    lv_obj_scroll_by(parent, 0, 25, LV_ANIM_OFF);
    lv_textarea_set_text(ta, input.c_str());
	lv_obj_add_event_cb(ta, input_history_ta_event_handler, LV_EVENT_ALL, active_ta);
    return ta;

}

lv_obj_t* Calculator::lv_result_ta(lv_obj_t* parent, std::string output, lv_obj_t* active_ta)
{
    lv_obj_t* ta = lv_textarea_create(parent);
    areas[total] = ta;
    total++;
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_width(ta, 320);
    lv_obj_align(ta, LV_ALIGN_BOTTOM_MID, 0, ( 35 * total));
    // Todo create dedicated eventhandler.
    lv_obj_add_state(ta, LV_STATE_DEFAULT); /*To be sure the cursor is visible*/
    lv_obj_set_style_text_align(ta, LV_TEXT_ALIGN_RIGHT, 0);
    lv_textarea_add_text(ta, output.c_str());
	lv_obj_add_event_cb(ta, input_history_ta_event_handler, LV_EVENT_ALL, active_ta);
    return ta;
}



