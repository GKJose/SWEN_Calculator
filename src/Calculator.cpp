#include <Calculator.h>
#include <ctime>
#include <string>
#include <sstream>
#include <unistd.h>
#include <regex>
#if ENABLE_MCP_KEYPAD
#include <Keypad.hxx>
#endif
#if ENABLE_GIAC
using namespace giac;
#endif
using namespace std;

/*Declarations*/
static lv_obj_t* textArea;
#if ENABLE_MCP_KEYPAD
static Keypad keypad;

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
	if(keypad.isPressed(X_SQUARED_BUTTON)){
			lv_textarea_add_text(textArea,"sqrt(");
	}else if(keypad.isPressed(LOG_BUTTON)){
		lv_textarea_add_text(textArea,"10^");
	}else if(keypad.isPressed(LN_BUTTON)){
		lv_textarea_add_text(textArea,"e^");
	}else if(keypad.isPressed(MODE_BUTTON)){
		lv_textarea_add_text(textArea,"^");
	}else if(keypad.isPressed(SETTINGS_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(LEFT_PARATHESIS_BUTTON)){
		lv_textarea_add_text(textArea,"sin(");
	}else if(keypad.isPressed(LEFT_BUTTON)){
		lv_textarea_add_text(textArea,"csc(");
	}else if(keypad.isPressed(Y_EQUALS_BUTTON)){
		//PI BUTTON
		lv_textarea_add_text(textArea,"3.14");
	}else if(keypad.isPressed(SEVEN_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(FOUR_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(ONE_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(ZERO_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(UP_BUTTON)){
		lv_textarea_add_text(textArea,"cos(");
	}else if(keypad.isPressed(SELECT_BUTTON)){
		lv_textarea_add_text(textArea,"sec(");
	}else if(keypad.isPressed(DOWN_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(EIGHT_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(FIVE_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(TWO_BUTTON)){
		//DO NOTHING;
	}else if(keypad.isPressed(DOT_SIGN_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(RIGHT_PARATHESIS_BUTTON)){
		lv_textarea_add_text(textArea,"tan(");
	}else if(keypad.isPressed(RIGHT_BUTTON)){
		lv_textarea_add_text(textArea,"cot(");
	}else if(keypad.isPressed(GRAPH_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(NINE_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(SIX_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(THREE_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(MINUS_SIGN_BUTTON)){
		//ANS BUTTON
	}else if(keypad.isPressed(CLEAR_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(DELETE_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(DIVIDE_BUTTON)){
		lv_textarea_add_text(textArea,"diff(");
	}else if(keypad.isPressed(MULTIPLY_BUTTON)){
		lv_textarea_add_text(textArea,"integrate(");
	}else if(keypad.isPressed(SUBTRACT_BUTTON)){
		lv_textarea_add_text(textArea,"factor(");
	}else if(keypad.isPressed(ADD_BUTTON)){
		//DO NOTHING
	}else if(keypad.isPressed(ENTER_BUTTON)){
		//ENTRY BUTTON
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
    lv_obj_add_event_cb(active_ta, active_ta_event_handler, LV_EVENT_ALL);
    lv_obj_add_state(active_ta, LV_STATE_FOCUSED);

    lv_keyboard_set_textarea(kb, active_ta); /*Focus it on one of the text areas to start*/

	if(first_screen)
	{
		/*Create a button to toggle the keyboard*/
		toggle_kb_btn = lv_btn_create(lv_scr_act());
		lv_obj_add_flag(toggle_kb_btn,LV_OBJ_FLAG_CHECKABLE);
		lv_obj_align(toggle_kb_btn, LV_ALIGN_TOP_RIGHT, 0, 0);
		lv_color_t grey = lv_palette_main(LV_PALETTE_GREY);
		lv_obj_set_style_bg_color(toggle_kb_btn, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
		lv_obj_set_size(toggle_kb_btn, 18, 18);
		lv_obj_t* kb_img = lv_img_create(toggle_kb_btn);
		lv_img_set_src(kb_img, LV_SYMBOL_KEYBOARD);
		lv_obj_align_to(kb_img, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_obj_add_event_cb(toggle_kb_btn, Calculator::toggle_kb_event_handler, LV_EVENT_ALL, toggle_kb_btn);
		/**/

		/*Create a button to clear the screen manually*/
		clear_scr_btn = lv_btn_create(lv_scr_act());
		lv_obj_align(clear_scr_btn, LV_ALIGN_TOP_LEFT, 0, 0);
		lv_obj_set_style_bg_color(clear_scr_btn, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
		lv_obj_set_size(clear_scr_btn, 18, 18);
		lv_obj_t* clear_scr_img = lv_img_create(clear_scr_btn);
		lv_img_set_src(clear_scr_img, LV_SYMBOL_CLOSE);
		lv_obj_align_to(clear_scr_img, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_obj_add_event_cb(clear_scr_btn, Calculator::clear_scr_btn_event_handler, LV_EVENT_ALL, parent);
		/**/
	}

    /*Put kb in view*/
    lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, -10);
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
        if (kb != NULL) lv_keyboard_set_textarea(kb, ta);
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
        
        /*Create the new text areas*/
        Calculator::lv_input_history_ta(parent, copy_input, ta);
	    Calculator::lv_result_ta(parent, output, ta);
        lv_obj_align(ta, LV_ALIGN_BOTTOM_MID, 0, ( 35 * total) + 35);
        lv_textarea_set_text(ta, "");
        lv_obj_scroll_to_view(ta, LV_ANIM_OFF);

        /*Put kb in view*/
        lv_obj_align_to(kb, parent, LV_ALIGN_BOTTOM_MID, 0, 0);
		lv_obj_scroll_to_view(kb, LV_ANIM_OFF);
		if(!lv_obj_has_flag(kb, LV_OBJ_FLAG_HIDDEN))
		{
			lv_obj_set_y(ta, lv_obj_get_y_aligned(ta) - 80);
		}
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
    if (!lv_obj_has_flag(kb, LV_OBJ_FLAG_HIDDEN))
    {
        lv_obj_set_y(ta, lv_obj_get_y_aligned(ta) - 80);
    }
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
    if (!lv_obj_has_flag(kb, LV_OBJ_FLAG_HIDDEN))
    {
        lv_obj_set_y(ta, lv_obj_get_y_aligned(ta) - 80);
    }
	lv_obj_add_event_cb(ta, input_history_ta_event_handler, LV_EVENT_ALL, active_ta);
    return ta;
}

std::string Calculator::convertDecimalToSEM(std::string number)
{
	//Convert the decimal to signed exponent mantissa
}

std::string Calculator::convertDecimalToHex(std::string number)
{
	//Convert decimal to hexidecimal
}
std::string Calculator::solveDecimalEquation(std::string equation)
{
	//Solve the equation provided
	//Use regex to pull operators/operands
	regex regexp("[0-9]+");
	smatch m;
	regex_search(equation,m,regexp);
	
	std::vector<int> operands;
	std::string output = "";
	for(auto operand:m){
		operands.push(std::stoi(operand));
	}
	
	regex regexp("[/,*,-,+]");
	regex_search(equation,m,regexp);
	
	for(auto opt: m){
		if(opt.compare("/")){
			if(operands[1] == 0){
				output = "ERROR: NaN";
			}else{
				output += (operands[0] / operands[1]);
			}
		}else if(opt.compare("*")){
			output += (operands[0] * operands[1]);
		}else if(opt.compare("-")){
			output += (operands[0] - operands[1]);
		}else{
			output += (operands[0] + operands[1]);
		}
	}
	
	return output;
	
}
bool Calculator::isValidEquation(std::string equation){
	 int8_t operandCount = 0;
	 int8_t operatorCount = 0;
	//Regex splits equation into tokens, which are the numbers
	regex regexp("[A-Z0-9]+");
	smatch m;
	regex_search(equation,m,regexp);
	for(auto token: m){
		operandCount++;
	}
	
	regex regexp("[\/,*,-,+]+");
	smatch m;
	regex_search(equation,m,regexp);
	for(auto token: m){
		operatorCount++;
	}
	return (operatorCount == (operandCount - 1)) || (operandCount > 2);
}

