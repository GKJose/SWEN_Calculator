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
	for(int btnID = x_BUTTON; btnID <= ENTER_BUTTON; btnID++){
		if(keypad.isPressed(btnID)){
			lv_event_send_recursive(lv_scr_act(),LV_EVENT_KEY_PRESSED,&btnID);
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
	lv_obj_add_state(outputTextArea,LV_STATE_DISABLED);
	

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
	   int btnID = (int*)lv_event_get_user_data(e);
	   cout << btnID << endl;
	   if(btnID == x_BUTTON){
		   lv_textarea_add_text(ta,"x");
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






