#ifndef SET_DATE_SETTINGS_MENU_INZ
#define SET_DATE_SETTINGS_MENU_INZ

#include <MenuCore.h>
#include <LCD.h>
#include <DateRTC.h>
#include <MainMenu.h>

class SetDateSettingsMenu : public MenuCore{
    
    char menuLine1_[19] = "Ustaw date";
    char menuLine2_[19] = "";
    char menuLine3_[19] = "";
    char menuLine4_[19] = "";
    
protected: 

    char pointer_position = 0x3;
    char max_pointer_position = 0x3;
    char min_pointer_position = 0x3;
    
public:
    char _enter_count = 0x0;
    
    char _buf_year;
    char _buf_month;
    char _buf_day;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    SetDateSettingsMenu(LCD *l, DateRTC *d, ModuleController *mc);
    virtual void display();
    virtual void onUp(MenuController*);
    virtual void onDown(MenuController*);
    virtual void onEnter(MenuController*);
    
};

#endif