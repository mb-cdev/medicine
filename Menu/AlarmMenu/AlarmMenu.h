#ifndef ALARM_MENU_INZ
#define ALARM_MENU_INZ

#include <MenuCore.h>
#include <MainMenu.h>

class AlarmMenu : public MenuCore
{
    char menuLine1_[19] = "";
    char menuLine2_[19] = "Wez pigulke";
    char menuLine3_[19] = "";
    char menuLine4_[19] = "ENTER:Wylacz alarm";
    
    bool alertVisible = true;
    long int lastAlertVisible = 0;
    
public:
    char max_pointer_position = 0x2;
    char min_pointer_position = 0x2;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    AlarmMenu(LCD *l, DateRTC *d, ModuleController *mc):MenuCore(l,d,mc){};
    
    virtual void onRefresh(MenuController *);
    virtual void onEnter(MenuController *);
};

#endif