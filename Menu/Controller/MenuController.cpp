#include <MenuController.h>

MenuController::MenuController(LCD *l, DateRTC *d, ModuleController *mc){
    
    DDRB &= 0b11011111;
    DDRC |= 0b00000011;
    
    menu = new MainMenu(l,d,mc);
}

void MenuController::init(){
    menu->display();
}

void MenuController::eventDownBtn(){
    menu->onDown(this);
}
void MenuController::eventEnterBtn(){
    menu->onEnter(this);
}
void MenuController::eventUpBtn(){
    menu->onUp(this);
}
void MenuController::eventRefresh(){
    menu->onRefresh(this);
}

void MenuController::setNewMenuObject(MenuCore *m){
    delete menu;
    
    menu = m;
    menu->display();
}

void MenuController::buttonListener()
{
    if((!(PINC & 0x2) && pushed_enter_btn)
        || (!(PINC & 0x1) && pushed_up_btn)
        || (!(PINB & 0x20) && pushed_down_btn))
    {
        pushed_enter_btn = false;
        pushed_up_btn = false;
        pushed_down_btn = false;
        delay(300);
    }
    
    else if((PINC & 0x1) && !pushed_up_btn)
    {
        pushed_up_btn = true;
        eventUpBtn();
    }
    else if((PINB & 0x20) && !pushed_down_btn)
    {
        pushed_down_btn = true;
        eventDownBtn();
    }
    else if((PINC & 0x2) && !pushed_enter_btn)
    {
        pushed_enter_btn = true;
        eventEnterBtn();
    }
    
    eventRefresh();
}