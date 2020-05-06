#ifndef SET_TIME_MENU_INZ
#define SET_TIME_MENU_INZ

#include <MenuCore.h>
#include <LCD.h>
#include <DateRTC.h>
#include <MainMenu.h>

class SetTimeMenu : public MenuCore{
    
    char menuLine1_[19] = "Ustaw godzine";
    char menuLine2_[19] = "";
    char menuLine3_[19] = "";
    char menuLine4_[19] = "";
    
protected: 

    char pointer_position = 0x3;
    char max_pointer_position = 0x3;
    char min_pointer_position = 0x3;
    
public:
    char _enter_count = 0x0;
    char _buf_hour = 0x0;
    char _buf_minute = 0x0;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    SetTimeMenu(LCD *l, DateRTC *d, ModuleController *mc);
    
    virtual void onUp(MenuController*);
    virtual void onDown(MenuController*);
    virtual void onEnter(MenuController*);
    virtual void display();
};

#endif