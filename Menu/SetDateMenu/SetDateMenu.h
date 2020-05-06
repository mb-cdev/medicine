#ifndef SET_DATE_MENU_INZ
#define SET_DATE_MENU_INZ

#include <MenuCore.h>
#include <MainMenu.h>

class SetDateMenu : public MenuCore
{
    char max_pointer_position = 0x4;
    char min_pointer_position = 0x2;
    
    char menuLine1_[19] = "Wybierz:";
    char menuLine2_[19] = "Ustaw Godzine";
    char menuLine3_[19] = "Ustaw Date";
    char menuLine4_[19] = "Menu glowne";
    
public:
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    SetDateMenu(LCD *l, DateRTC *d, ModuleController *mc):MenuCore(l,d,mc){};
    
    virtual void onUp(MenuController*);
    virtual void onDown(MenuController*);
    virtual void onEnter(MenuController*);
};

#endif