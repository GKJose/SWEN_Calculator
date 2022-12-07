#include <Calculator.h>
#include <ctime>
#include <string>
#include <sstream>
#include <unistd.h>
#include <thread>
#if ENABLE_MCP_KEYPAD
#include <Keypad.hxx>
#endif

using namespace std;

/*Declarations*/
static lv_obj_t* textArea,*outputTextArea;
static string initialText = "Welcome to Cyberbits01 Calculator!\nEnter any equation, or single number.\nSEM-H/SEM-B as follows [0x0,0x00,0x0..0]\n[0,0...0,0...0]\nDecimal as 25.0 or 25\nBinary as 0....1\nValid operations are *,-,+.";
#if ENABLE_MCP_KEYPAD

static Keypad keypad;
static int btnID;
#endif


static lv_obj_t* tabview;
extern std::string mode;
void Calculator::createDemo(){
	tabview = lv_main_screen_tabs();

}
void Calculator::update(lv_timer_t * timer){
	#if ENABLE_MCP_KEYPAD 
	keypad.poll();
	for(int btn = x_BUTTON; btn <= ENTER_BUTTON;btn++){
		if(keypad.isPressed(btn)){
			if(btn == HOME_BUTTON){

			}else if(btn == SETTINGS_BUTTON){

			}else if(btn == RESET_BUTTON){
				lv_textarea_set_text(textArea,"");
				lv_textarea_set_text(outputTextArea,initialText.c_str());
			}else{
				btnID = btn;
				lv_event_send_recursive(lv_scr_act(),LV_EVENT_KEY_PRESSED,&btnID);
			}
			
			return;
		}
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
	lv_obj_add_state(outputTextArea,LV_STATE_DEFAULT);
	lv_obj_add_event_cb(outputTextArea,output_ta_event_handler,LV_EVENT_ALL,nullptr);
	lv_textarea_set_text(outputTextArea,initialText.c_str());

}

/*Callback functions*/
static void Calculator::input_ta_event_handler(lv_event_t* e)
{   
	
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* parent = lv_obj_get_parent(ta);
	if(!lv_obj_is_visible(ta)){
		return;
	}
	#if ENABLE_MCP_KEYPAD
   	if(code == LV_EVENT_KEY_PRESSED){
	   int btnID = *(int*)lv_event_get_param(e);
	   if(btnID == x_BUTTON){
		   lv_textarea_add_text(ta,"x");
	   }else if(btnID == A_BUTTON){
		   lv_textarea_add_text(ta,"A");
	   }else if(btnID == B_BUTTON){
		   lv_textarea_add_text(ta,"B");
	   }else if(btnID == C_BUTTON){
		   lv_textarea_add_text(ta,"C");
	   }else if(btnID == D_BUTTON){
		   lv_textarea_add_text(ta,"D");
	   }else if(btnID == E_BUTTON){
		   lv_textarea_add_text(ta,"E");
	   }else if(btnID == F_BUTTON){
		   lv_textarea_add_text(ta,"F");
	   }else if(btnID == LEFT_BUTTON){
		   lv_textarea_cursor_left(ta);
	   }else if(btnID == SEVEN_BUTTON){
		   lv_textarea_add_text(ta,"7");
	   }else if(btnID == FOUR_BUTTON){
		   lv_textarea_add_text(ta,"4");
	   }else if(btnID == ONE_BUTTON){
		   lv_textarea_add_text(ta,"1");
	   }else if(btnID == b_BUTTON){
		   lv_textarea_add_text(ta,"b");
	   }else if(btnID == COMMA_BUTTON){
		   lv_textarea_add_text(ta,",");
	   }else if(btnID == EIGHT_BUTTON){
		   lv_textarea_add_text(ta,"8");
	   }else if(btnID == FIVE_BUTTON){
		   lv_textarea_add_text(ta,"5");
	   }else if(btnID == TWO_BUTTON){
		   lv_textarea_add_text(ta,"2");
	   }else if(btnID == ZERO_BUTTON){
		   lv_textarea_add_text(ta,"0");
	   }else if(btnID == RESET_BUTTON){
		   lv_textarea_set_text(ta,"");
	   }else if(btnID == RIGHT_BUTTON){
		   lv_textarea_cursor_right(ta);
	   }else if(btnID == LEFT_BRACKET_BUTTON){
		   lv_textarea_add_text(ta,"[");
	   }else if(btnID == NINE_BUTTON){
		   lv_textarea_add_text(ta,"9");
	   }else if(btnID == SIX_BUTTON){
		   lv_textarea_add_text(ta,"6");
	   }else if(btnID == THREE_BUTTON){
		   lv_textarea_add_text(ta,"3");
	   }else if(btnID == DOT_SIGN_BUTTON){
		   lv_textarea_add_text(ta,".");
	   }else if(btnID == CLEAR_BUTTON){
		   lv_textarea_set_text(ta,"");
	   }else if(btnID == DELETE_BUTTON){
		   lv_textarea_del_char(ta);
	   }else if(btnID == RIGHT_BRACKET_BUTTON){
		   lv_textarea_add_text(ta,"]");
	   }else if(btnID == MULTIPLY_BUTTON){
		   lv_textarea_add_text(ta,"*");
	   }else if(btnID == SUBTRACT_BUTTON){
		   lv_textarea_add_text(ta,"-");
	   }else if(btnID == ADD_BUTTON){
		   lv_textarea_add_text(ta,"+");
	   }else if(btnID == ENTER_BUTTON){
		   lv_event_send(ta,LV_EVENT_READY,nullptr);
	   }
   }
   #endif
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
static void output_ta_event_handler(lv_event_t* e){

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* parent = lv_obj_get_parent(ta);
	if(!lv_obj_is_visible(ta)){
		return;
	}
	#if ENABLE_MCP_KEYPAD
   	if(code == LV_EVENT_KEY_PRESSED){
	   int btnID = *(int*)lv_event_get_param(e);
	   if(btnID == UP_BUTTON){
		   lv_textarea_cursor_up(ta);
	   }else if(btnID == DOWN_BUTTON){
		   lv_textarea_cursor_down(ta);
	   }
	}
	#endif
}





