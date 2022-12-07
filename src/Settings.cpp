//Settings.cpp
//************************************************************
//*                                                          
//* Author: Mendez, Jose - Cyberbits01
//*`Purpose: Provides the GUI code, nad backend code for the settings tab
//*
//* Contains:                                        |UPDATE
//*  Settings (Constructor)..........................|
//*  
//* 
//*
//* Date: 16Nov22
//************************************************************


#include <Settings.hxx>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <lvgl.h>
#include <lvgl/src/core/lv_event.h>
#include <Calculator.h>
#include <stdio.h>
#include <sstream>



lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt, lv_menu_builder_variant_t builder_variant);
lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val);
lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk);
lv_obj_t * create_button(lv_obj_t * parent, const char * txt);
void* setting;

LV_IMG_DECLARE(button_map);
std::string mode;
class Settings{
    using container = lv_obj_t;
    using page = lv_obj_t;
    using section = lv_obj_t;
   
    
    lv_obj_t *parent, *menu, *root_page, *sub_display_page,*sub_help_page, *sub_about_page;
    std::map<section*, std::vector<container*>> container_map;
    std::map<page*, std::vector<section*>> section_map;
    public:
    
    Settings(lv_obj_t* parent):parent(parent),menu(lv_menu_create(parent)){
        setting = this;
        lv_menu_set_mode_root_back_btn(menu,LV_MENU_ROOT_BACK_BTN_DISABLED);
        lv_obj_add_event_cb(menu,back_event_handler,LV_EVENT_CLICKED,menu);
        lv_obj_set_size(menu,LV_HOR_RES,LV_VER_RES - 20);
        lv_obj_center(menu);

        lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
        lv_obj_set_style_bg_color(menu, lv_color_darken(bg_color, 10), 0);

        init_root_page();
        init_display_page();
        //init_help_page();
        init_about_page();

        lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, nullptr);  
        
    }
    private:
//************************************************************
//* back_event_handler
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: back_event_handler(event)
//*     event = The lvgl event obj
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   lv_event_get_code                    lvgl.a
//*   lv_event_get_target                  lvgl.a
//*   lv_obj_add_flag                      lvgl.a                            
//*   
//* Date: 16Nov22
//************************************************************
    static void back_event_handler(lv_event_t * e){
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t* obj = lv_event_get_target(e);
        if(code == LV_EVENT_CLICKED){
            lv_obj_add_flag(obj,LV_OBJ_FLAG_OVERFLOW_VISIBLE);
        }
    }
//************************************************************
//* slider_event_cb
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: slider_event_cb(event)
//*     event = The lvgl event obj
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   lv_event_get_target                    lvgl.a
//*   lv_slider_get_value                         
//*   
//* Date: 16Nov22
//************************************************************
    static void slider_event_cb(lv_event_t * e){
        lv_obj_t * slider = lv_event_get_target(e);
        #if ENABLE_MCP_KEYPAD
        softPwmWrite(5,(int)lv_slider_get_value(slider));
        std::cout << (int)lv_slider_get_value(slider) + "\n";
        #endif 
    }
//************************************************************
//* init_page
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: init_page()
//*     
//*
//* Returns: A blank lv_obj page
//*
//* Functions called:                   Source:
//*   lv_menu_page_create                Settings.cpp
//*   lv_obj_set_style_pad_hor           lvgl.a
//*   lv_menu_separator_create           lvgl.a                         
//*   
//* Date: 16Nov22
//************************************************************
    page* init_page(){
        LV_ASSERT(menu!=nullptr);
        page* obj = lv_menu_page_create(menu, nullptr);
        lv_obj_set_style_pad_hor(obj, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu),0),0);
        lv_menu_separator_create(obj);
        return obj;
    }
//************************************************************
//* create_section
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_section()
//*     
//*
//* Returns: A blank lv_obj section
//*
//* Functions called:                   Source:
//*   lv_menu_section_create               lvgl.a                         
//*   
//* Date: 16Nov22
//************************************************************
    section* create_section(page* p){
        section* obj = lv_menu_section_create(p);
        if (section_map.find(p) == section_map.end()){
            section_map[p] = std::vector<section*>{obj};
        } else {
            section_map[p].push_back(obj);
        }
        return obj;
    }
//************************************************************
//* create_container
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_container()
//*
//* Returns: A blank lv_obj container.
//*
//* Functions called:                   Source:
//*   lv_menu_cont_create                 Settings.cpp                           
//*   
//* Date: 16Nov22
//************************************************************
    container* create_container(section* p){
        container* obj = lv_menu_cont_create(p);
        if (container_map.find(p) == container_map.end()){
            container_map[p] = std::vector<container*>{obj};
        } else {
            container_map[p].push_back(obj);
        }
        return obj;
    }
//************************************************************
//* create_root_text_container
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_root_text_container()
//*    
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   create_container                      Settings.cpp
//*   create_text                           Settings.cpp
//*   lv_menu_set_load_page_event           lvgl.a                          
//*   
//* Date: 16Nov22
//************************************************************
    container* create_root_text_container(page* p, const char* icon, const char* name){
        LV_ASSERT(root_page!=nullptr);
        LV_ASSERT(section_map.find(root_page) != section_map.end());
        LV_ASSERT(section_map[root_page].size() > 0);
        container* rc = create_container(section_map[root_page][0]);
        lv_obj_t* rc_text = create_text(rc, icon, name, LV_MENU_ITEM_BUILDER_VARIANT_1);
        lv_menu_set_load_page_event(menu, rc, p);
        return rc;
    }
//************************************************************
//* init_root_page
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: init_root_page()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   lv_menu_page_create                 Settings.cpp
//*   lv_obj_set_style_pad_hor            lvgl.a
//*   create_section                      Settings.cpp
//*   lv_menu_set_sidebar_page            lvgl.a                          
//*   
//* Date: 16Nov22
//************************************************************
    void init_root_page(){
        root_page = lv_menu_page_create(menu, (char*)"Settings");
        lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
        section* sec = create_section(root_page);
        lv_menu_set_sidebar_page(menu, root_page);
    }
//************************************************************
//* init_display_page
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: init_display_page()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   init_page                             Settings.cpp
//*   create_section                        Settings.cpp
//*   create_container                      Settings.cpp
//*   create_slider                         Settings.cpp
//*   lv_obj_add_event_cb                   lvgl.a
//*   create_root_text_container            Settings.cpp                           
//*   
//* Date: 16Nov22
//************************************************************
    void init_display_page(){
        sub_display_page = init_page();
        section* sec = create_section(sub_display_page);
        container* con = create_container(sec);
        lv_obj_t* slider = create_slider(con, LV_SYMBOL_SETTINGS, "Brightness", 25, 100, 100);
        lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
        create_root_text_container(sub_display_page, LV_SYMBOL_IMAGE, "Display");
    }
//************************************************************
//* init_help_page
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: init_help_page()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   init_page                             Settings.cpp
//*   create_section                        Settings.cpp
//*   create_container                      Settings.cpp
//*   create_slider                         Settings.cpp
//*   lv_obj_add_event_cb                   lvgl.a
//*   create_root_text_container            Settings.cpp                           
//*   
//* Date: 16Nov22
//************************************************************
    void init_help_page(){
        sub_help_page = init_page();
        section* sec = create_section(sub_help_page);
        container* con = create_container(sec);

        lv_obj_t* buttonMapImg = lv_img_create(con);
        lv_img_set_src(buttonMapImg,&button_map);
        lv_obj_align(buttonMapImg,LV_ALIGN_CENTER,0,0);
        

        //lv_obj_set_size(table,LV_SIZE_CONTENT,LV_SIZE_CONTENT);

        create_root_text_container(sub_help_page, LV_SYMBOL_IMAGE, "Help");

    }
//************************************************************
//* init_about_page
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: init_about_page()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   init_page                             Settings.cpp
//*   create_section                        Settings.cpp
//*   create_container                      Settings.cpp
//*   create_slider                         Settings.cpp
//*   lv_obj_add_event_cb                   lvgl.a
//*   create_root_text_container            Settings.cpp                           
//*   
//* Date: 16Nov22
//************************************************************
    void init_about_page(){
        sub_about_page = init_page();
        section* sec = create_section(sub_about_page);
        container* con = create_container(sec);
        lv_obj_t* text = create_text(con, nullptr, "Software Version: Alpha 1", LV_MENU_ITEM_BUILDER_VARIANT_1);
        create_root_text_container(sub_about_page, LV_SYMBOL_WARNING, "About");
    }


};
//************************************************************
//* createSettingsTab
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: createSettingsTab()
//*     
//*
//* Returns: N/A
//*
//* Functions called:                   Source:
//*   softPwmCreate                         wiringPi.a
//*   softPwmWrite                          wiringPi.a                         
//*   
//* Date: 16Nov22
//************************************************************
void createSettingsTab(lv_obj_t* parent){
    
    static Settings settings(parent);
    #if ENABLE_MCP_KEYPAD
    softPwmCreate(5,100,100);
    softPwmWrite(5,100);
    #endif
	
}
//************************************************************
//* create_text
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_text(parent,icon,txt,build_variant)
//*         parent - lv_obj parent
//*         icon   - lv icon
//*         txt    - the text to be displayed
//*         build_variant - ...
//*     
//*
//* Returns: lv_obj text
//*
//* Functions called:                   Source:
//*     lv_img_create                       lvgl.a
//*     lv_img_set_src                      lvgl.a
//*     lv_label_create                     lvgl.a
//*     lv_label_set_text                   lvgl.a
//*     lv_set_long_mode                    lvgl.a
//*     lv_obj_set_flex_grow                lvgl.a
//*     lv_obj_add_flag                     lvgl.a
//*     lv_obj_swap                         lvgl.a                   
//*   
//* Date: 16Nov22
//************************************************************
lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t* obj = parent;
    
    
    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}
//************************************************************
//* create_slider
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_slider(parent,icon,txt,min,max,val)
//*         parent - lv_obj parent
//*         icon   - lv icon
//*         txt    - the text to be displayed
//*         min - the min slider value
//*         max - the max slider value
//*         val - inital value
//*     
//*
//* Returns: lv_obj slider
//*
//* Functions called:                   Source:
//*                    
//*   
//* Date: 16Nov22
//************************************************************
lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max,
                                int32_t val)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);

    if(icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return slider;
}
//************************************************************
//* create_switch
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_switch(parent,icon,txt,chk)
//*         parent - lv_obj parent
//*         icon   - lv icon
//*         txt    - the text to be displayed
//*         chk    - the initial value
//*     
//*
//* Returns: lv_obj switch
//*
//* Functions called:                   Source:
//*                    
//*   
//* Date: 16Nov22
//************************************************************
lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return obj;
}
//************************************************************
//* create_button
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: create_button(parent,icon,txt)
//*         parent - lv_obj parent
//*         icon   - lv icon
//*         txt    - the text to be displayed
//*     
//*
//* Returns: lv_obj button
//*
//* Functions called:                   Source:
//*                    
//*   
//* Date: 16Nov22
//************************************************************
lv_obj_t * create_button(lv_obj_t * parent, const char * txt){
	lv_obj_t * label;
	
	lv_obj_t * btn = lv_btn_create(parent);
	label = lv_label_create(btn);
	lv_label_set_text(label,txt);
	lv_obj_set_flex_grow(label, 1);
	
	return btn;
}
