#ifndef MENU_CORE_INZ
#define MENU_CORE_INZ

#include <LCD.h>
#include <DateRTC.h>
#include <ModuleController.h>

class MenuController;

class MenuCore{
    
    void setPointerOnScreen();
    
    char menuLine1_[19] = "Line1";
    char menuLine2_[19] = "Line2";
    char menuLine3_[19] = "Line3";
    char menuLine4_[19] = "Line4";

public:
    char pointer_position = 0x1;
    char max_pointer_position = 0x4;
    char min_pointer_position = 0x1;
    
    LCD *lcd;
    DateRTC *dRTC;
    ModuleController *moduleController;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    MenuCore(LCD *l, DateRTC *d, ModuleController *mc);
    void pointerUp();
    void pointerDown();
    virtual void onEnter(MenuController *);
    virtual void onUp(MenuController *);
    virtual void onDown(MenuController *);
    virtual void onRefresh(MenuController *);
    virtual void display();
    LCD *getLCD();
    DateRTC *getRTC();
    ModuleController *getModuleController();
};
#endif