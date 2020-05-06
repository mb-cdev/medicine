#ifndef MAIN_MENU_INZ
#define MAIN_MENU_INZ

#include <LCD.h>
#include <MenuCore.h>
#include <SetDateMenu.h>
#include <AddNewXYModuleMenu.h>
#include <SetContainerMenu.h>

class MainMenu : public MenuCore
{
    char max_pointer_position = 0x4;
    char min_pointer_position = 0x2;
    unsigned long int time = 0;
    
    char menuLine1_[19] = "";
    char menuLine2_[19] = "Ustaw pojemnik";
    char menuLine3_[19] = "Ustaw date i godz.";
    char menuLine4_[19] = "Dodaj modul XY";
public:
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    MainMenu(LCD *l, DateRTC *d, ModuleController *mc):MenuCore(l,d,mc){};
    virtual void onEnter(MenuController *);
    virtual void onUp(MenuController *);
    virtual void onDown(MenuController *);
    virtual void onRefresh(MenuController *);
};
#endif