#ifndef SET_CONTAINER_MENU_INZ
#define SET_CONTAINER_MENU_INZ

#include <MenuCore.h>
#include <SetDateSettingsMenu.h>
#include <SetTimeMenu.h>
#include <Globals.h>
#include <MainMenu.h>

class SetDateSettingsMenu;
class SetTimeMenu;

class SetContainerMenu : public MenuCore
{
    char menuLine1_[19] = "";
    char menuLine2_[19] = "Wybierz pojemnik";
    char menuLine3_[19] = "";
    char menuLine4_[19] = "Enter: Dalej";
    
    char _buf_container_x = 0x0;
    char _buf_container_y = 0x0;
    
    char _buf_year = 0x0;
    char _buf_month = 0x0;
    char _buf_day = 0x0;
    char _buf_hour = 0x0;
    char _buf_minute = 0x0;
    
    char _enter_count = 0x0;
    bool blinkEnabled = true;
    
    unsigned long int toggleBlinkTime = 0;
    
    SetDateSettingsMenu *dateMenu;
    SetTimeMenu *timeMenu;
    
public:

    char max_pointer_position = 0x2;
    char min_pointer_position = 0x2;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    
    virtual void display();
    
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    virtual void onUp(MenuController*);
    virtual void onDown(MenuController*);
    virtual void onEnter(MenuController*);
    virtual void onRefresh(MenuController*);
    
    SetContainerMenu(LCD *l,DateRTC *d,ModuleController *mc):MenuCore(l,d,mc){};
    void printContainerTime(char, char);
};

#endif