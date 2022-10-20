#include <Calculator.h>
#include <stdio.h>
#include <tabs.hxx>



lv_obj_t* lv_main_screen_tabs(void)
{
    /*Create a Tab view object*/
    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 20);
    lv_obj_add_event_cb(lv_tabview_get_content(tabview), [](lv_event_t* e){
        if (e->code == LV_EVENT_SCROLL_BEGIN) {
            lv_anim_t* a = (decltype(a))e->param;
            if (a) a->time = 0;
        }
    }, LV_EVENT_SCROLL_BEGIN, NULL);

    /*Change style*/
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS | LV_STATE_CHECKED);
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Main");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Settings");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview,"Help");

    lv_obj_set_scrollbar_mode(tab1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(tab3, LV_SCROLLBAR_MODE_OFF);
    

    /*Add content to the tabs*/
    Calculator::main_screen_driver(tab1);
    createSettingsTab(tab2);
    createHelpTab(tab3);
    
    return tabview;

}
