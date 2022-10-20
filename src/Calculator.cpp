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
static lv_obj_t* textArea,*outputTextArea;
#if ENABLE_MCP_KEYPAD
static Keypad keypad;
#endif


static lv_obj_t* tabview;
extern std::string mode;
void Calculator::createDemo(){
	tabview = lv_main_screen_tabs();


}
void Calculator::update(lv_timer_t * timer){
	
	#if ENABLE_MCP_KEYPAD
	keypad.poll();
	if(keypad.isPressed(x_BUTTON)){
		lv_textarea_add_text(textArea,"x");
	}
	else if(keypad.isPressed(A_BUTTON)){
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
	else if(keypad.isPressed(HOME_BUTTON)){
		lv_tabview_set_act(tabview,0,LV_ANIM_OFF);
	}else if(keypad.isPressed(LEFT_BUTTON)){
		lv_textarea_cursor_left(textArea);
	}else if(keypad.isPressed(SETTINGS_BUTTON)){
		lv_tabview_set_act(tabview,1,LV_ANIM_OFF);
	}else if(keypad.isPressed(SEVEN_BUTTON)){
		lv_textarea_add_text(textArea,"7");
	}else if(keypad.isPressed(FOUR_BUTTON)){
		lv_textarea_add_text(textArea,"4");
	}else if(keypad.isPressed(ONE_BUTTON)){
		lv_textarea_add_text(textArea,"1");
	}else if(keypad.isPressed(b_BUTTON)){
		lv_textarea_add_text(textArea,"b");
	}else if(keypad.isPressed(UP_BUTTON)){
		lv_obj_scroll_by(outputTextArea,0,-10,LV_ANIM_ON);
	}else if(keypad.isPressed(COMMA_BUTTON)){
		lv_textarea_add_text(",");
	}else if(keypad.isPressed(DOWN_BUTTON)){
		lv_obj_scroll_by(outputTextArea,0,10,LV_ANIM_ON);
	}else if(keypad.isPressed(EIGHT_BUTTON)){
		lv_textarea_add_text(textArea,"8");
	}else if(keypad.isPressed(FIVE_BUTTON)){
		lv_textarea_add_text(textArea,"5");
	}else if(keypad.isPressed(TWO_BUTTON)){
		lv_textarea_add_text(textArea,"2");
	}else if(keypad.isPressed(ZERO_BUTTON)){
		lv_textarea_add_text(textArea,"0");
	}else if(keypad.isPressed(RESET_BUTTON)){
		lv_textarea_set_text(textArea,"");
		lv_textarea_set_text(outputTextArea,"");
	}else if(keypad.isPressed(RIGHT_BUTTON)){
		lv_textarea_cursor_right(textArea);
	}else if(keypad.isPressed(LEFT_BRACKET_BUTTON)){
		lv_textarea_add_text(textArea,"[");
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
	}else if(keypad.isPressed(RIGHT_BRACKET_BUTTON)){
		lv_textarea_add_text(textArea,"]");
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
void Calculator::main_screen_driver(lv_obj_t* parent)
{
	
    textArea = lv_textarea_create(parent);

    lv_textarea_set_one_line(textArea,true);
    lv_obj_set_width(textArea, 320);
	lv_obj_set_height(textArea,40);
    lv_obj_align(textArea, LV_ALIGN_BOTTOM_MID, 0, 10);
    lv_obj_add_event_cb(textArea, input_ta_event_handler, LV_EVENT_ALL,nullptr);
    lv_obj_add_state(textArea, LV_STATE_FOCUSED);

	outputTextArea = lv_textarea_create(parent);
	lv_obj_set_width(outputTextArea,320);
	lv_obj_set_height(outputTextArea,175);
	lv_obj_align(outputTextArea,LV_ALIGN_TOP_MID,0,-10);
	lv_obj_add_state(outputTextArea,LV_STATE_DISABLED);
	

}

/*Callback functions*/
static void Calculator::input_ta_event_handler(lv_event_t* e)
{   
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* parent = lv_obj_get_parent(ta);
   if (code == LV_EVENT_READY)
    {
		// Set the solution to the string output, the rest of the code handles displaying the result
    	string output = "";
		
        const char *copy_input = lv_textarea_get_text(textArea);
		auto [operands,opt,inputCode] = parseInput(copy_input);
		if(inputCode <= 0){
			output = "ERROR: Check input\n";
			output += copy_input;
		
		}else if(inputCode == 1){
			output = operands.at(0).toString();
		}else if(inputCode == 2){
			std::cout << "Equation is valid!\n";
			output += copy_input;
			output += "-----------------\n";
			output += operands.at(0).toString();
			output += "----------------\n";
			output += operands.at(1).toString();
			output += "----------------\n";
			
			if(opt.compare("*") == 0){
				output += (operands.at(0) * operands.at(1)).toString();
			}else if(opt.compare("-") == 0){
				output += (operands.at(0) - operands.at(1)).toString();
			}else if(opt.compare("+") == 0){
				output += (operands.at(0) + operands.at(1)).toString();
			}
		}
		std::cout << output;
		lv_textarea_set_text(outputTextArea,output.c_str());
		lv_textarea_set_text(textArea,"");
		lv_obj_scroll_to(outputTextArea,0,0,LV_ANIM_ON);
	}
  
	
}






