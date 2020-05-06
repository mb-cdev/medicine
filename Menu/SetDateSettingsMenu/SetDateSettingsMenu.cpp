#include <SetDateSettingsMenu.h>
#include <MenuController.h>

SetDateSettingsMenu::SetDateSettingsMenu(LCD *l, DateRTC *d, ModuleController *mc): MenuCore(l,d,mc){
    _buf_year = d->currentDate.year;
    _buf_day = d->currentDate.day;
    _buf_month = d->currentDate.month;
}

void SetDateSettingsMenu::display(){
    sprintf(menuLine3_, "2%03d-%02d-%02d",_buf_year , _buf_month, _buf_day );
    
    lcd->printLines(menuLine1(),menuLine2(),menuLine3(),menuLine4());
    pointer_position = minPointerPosition();
    lcd->setPointerInLine(minPointerPosition());
}

void SetDateSettingsMenu::onUp(MenuController *m){
    switch(_enter_count){
        case 0x2:
            ++_buf_day;
            if(_buf_day > 31 && _buf_month != 2){
                _buf_day = 1;
            }else if(_buf_day > 29 && _buf_month == 2){
                _buf_day = 1;
            }
            
            break;
        case 0x1:
            if(++_buf_month > 12)
                _buf_month = 1;
            break;
        case 0x0:
            if(++_buf_year > 99)
                _buf_year = 0;
            break;
    }
    display();
}

void SetDateSettingsMenu::onDown(MenuController *m){
    switch(_enter_count){
        case 0x2:
            --_buf_day;
            if(_buf_day < 1 && _buf_month != 2){
                _buf_day = 31;
            }else if(_buf_day < 1 && _buf_month == 2){
                _buf_day = 29;
            }
            break;
        case 0x1:
            if(--_buf_month < 1)
                _buf_month = 12;
            break;
        case 0x0:
            if(--_buf_year < 1)
                _buf_year = 99;
            break;
    }
    display();
}


void SetDateSettingsMenu::onEnter(MenuController *m){
    _enter_count++;
    
    if(_enter_count == 0x1){
        dRTC->setYear(_buf_year);
    }else if(_enter_count == 0x2){
        dRTC->setMonth(_buf_month);
    }else if(_enter_count == 0x3){
        dRTC->setDay(_buf_day);
    }else if(_enter_count >= 0x4){
        MainMenu *newMenu = new MainMenu(getLCD(), getRTC(),getModuleController());
        m->setNewMenuObject(newMenu);
    }
}