#ifndef MENU_CONTROLLER_INZ
#define MENU_CONTROLLER_INZ

#include <LCD.h>
#include <Arduino.h>
#include <MainMenu.h>
#include <DateRTC.h>
#include <ModuleController.h>

/**
 * PORT - PIN => PRZEZNACZENIE
 * BTN:
 * 1 - LEWO
 * 2 - GÓRA
 * 3 - DÓŁ
 * 4 - PRAWO 
 * 5 - ENTER
 * OD LEWEJ STRONY BUTTONY LICZONE
 * PORTB - 3 => 1, 4 => 2, 5 => 3
 * PORTC - 0 => 4, 1 => 5
 * */

class MenuController{
    
    bool pushed_left_btn = false;
    bool pushed_right_btn = false;
    bool pushed_up_btn = false;
    bool pushed_down_btn = false;
    bool pushed_enter_btn = false;
    
    void eventUpBtn();
    void eventDownBtn();
    void eventRightBtn();
    void eventLeftBtn();
    void eventEnterBtn();
    void eventRefresh();
    
public:
    MenuCore * menu;
    MenuController(LCD*, DateRTC*, ModuleController*);
    void buttonListener();
    void init();
    void setNewMenuObject(MenuCore*);
};

#endif