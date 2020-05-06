#include <SetTimeMenu.h>
#include <MenuController.h>

void SetTimeMenu::onUp(MenuController *m){
    switch(_enter_count){
        case 0x0:
            if(++_buf_hour > 23)
                _buf_hour = 0;
            break;
        case 0x1:
            if(++_buf_minute > 59)
                _buf_minute = 0;
            break;
    }
    
    display();
}
void SetTimeMenu::onDown(MenuController *m){
    switch(_enter_count){
        case 0x0:
            if(--_buf_hour < 0)
                _buf_hour = 23;
            break;
        case 0x1:
            if(--_buf_minute < 0)
                _buf_minute = 59;
            break;
    }
    display();
}
void SetTimeMenu::display()
{
    sprintf(menuLine3_, "%02d:%02d", _buf_hour, _buf_minute);
    
    lcd->printLines(menuLine1(),menuLine2(),menuLine3(),menuLine4());
    pointer_position = minPointerPosition();
    lcd->setPointerInLine(minPointerPosition());
}

void SetTimeMenu::onEnter(MenuController *m)
{
    _enter_count++;
    if(_enter_count == 0x1)
    {
        dRTC->setHour(_buf_hour);
    }
    else if(_enter_count == 0x2)
    {
        dRTC->setMinute(_buf_minute);
    }
    else if(_enter_count >= 0x3)
    {
        dRTC->resetSeconds();
        MainMenu *mainMenu = new MainMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(mainMenu);
    }
}

SetTimeMenu::SetTimeMenu(LCD *l, DateRTC *d, ModuleController *mc):MenuCore(l,d,mc){
    _buf_hour = d->currentDate.hour;
    _buf_minute = d->currentDate.minute;
}