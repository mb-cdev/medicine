#ifndef XY_MODULE_INZ
#define XY_MODULE_INZ

#include <MenuCore.h>
#include <Globals.h>

class AddNewXYModuleMenu : public MenuCore{
    
    char menuLine1_[19] = "1.Wybierz os:";
    char menuLine2_[19] = "X";
    char menuLine3_[19] = "2.Podlacz modul";
    char menuLine4_[19] = "Enter: Anuluj";
    
    char _buf_axis = 0;
    
    char addressAddedLine[19] = "Modul dodany!";
    char addressNotAddedLine[19] = "Brak miejsca";
    char enterToContinue[19] = "Enter: menu glowne";

public:
    char max_pointer_position = 0x2;
    char min_pointer_position = 0x2;
    MODULE_AXIS current_axis = MODULE_AXIS::X;
    
    virtual char *menuLine1() { return menuLine1_; };
    virtual char *menuLine2() { return menuLine2_; };
    virtual char *menuLine3() { return menuLine3_; };
    virtual char *menuLine4() { return menuLine4_; };
    virtual char maxPointerPosition() { return max_pointer_position; };
    virtual char minPointerPosition() { return min_pointer_position; };
    
    virtual void onUp(MenuController*);
    virtual void onDown(MenuController*);
    virtual void onEnter(MenuController*);
    virtual void onRefresh(MenuController*);
    
    AddNewXYModuleMenu(LCD *l, DateRTC *d, ModuleController *mc):MenuCore(l,d,mc){}
};

#endif