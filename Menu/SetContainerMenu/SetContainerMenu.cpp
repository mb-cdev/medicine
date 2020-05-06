#include <SetContainerMenu.h>
#include <MenuController.h>

void SetContainerMenu::printContainerTime(char container_x, char container_y)
{
    char timeChar[19] = "";
    //schar containerPosition[10] = "";
    
    execute_time setTime = getModuleController()->containers[container_x][container_y].time;
    sprintf(timeChar, "20%02d-%02d-%02d %02d:%02d",setTime.year,setTime.month,setTime.day,setTime.hour,setTime.minute);
    //sprintf(containerPosition, "X: %d Y: %d", container_x, container_y);
    
    getLCD()->print(timeChar,0x3);
    //getLCD()->print(containerPosition,0x1);
}

void SetContainerMenu::onUp(MenuController *m)
{
    if(_enter_count == 0x0)
    {
        getModuleController()->setContainerStatus(_buf_container_x, _buf_container_y, 0x0);
        _buf_container_x++;
    
        if(_buf_container_x > (MAX_MODULES - 1))
        {        
            _buf_container_y++;
            if(_buf_container_y > (MAX_MODULES - 1)){
                _buf_container_y = 0x0;
            }
            _buf_container_x = 0x0;
        }
        printContainerTime(_buf_container_x, _buf_container_y);
    }
    else if(_enter_count >= 0x1 && _enter_count <= 0x4)
    {
        dateMenu->onUp(m);
    }
    else if(_enter_count >= 0x5 && _enter_count <= 0x7)
    {
        timeMenu->onUp(m);
    }
    
}

void SetContainerMenu::onDown(MenuController *m)
{
    if(_enter_count == 0x0)
    {
        
        getModuleController()->setContainerStatus(_buf_container_x, _buf_container_y, 0x0);
        _buf_container_x--;
        
        if(_buf_container_x < 0)
        {    
            _buf_container_y--;
            if(_buf_container_y < 0){
                _buf_container_y = MAX_MODULES-1;
            }
            _buf_container_x = MAX_MODULES-1;
        }
        printContainerTime(_buf_container_x, _buf_container_y);
    }
    else if(_enter_count >= 0x1 && _enter_count <= 0x4)
    {
        dateMenu->onDown(m);
    }
    else if(_enter_count >= 0x5 && _enter_count <= 0x7)
    {
        timeMenu->onDown(m);
    }
}

void SetContainerMenu::onRefresh(MenuController *m)
{
    if((!toggleBlinkTime || (millis() - toggleBlinkTime >= 750)) && blinkEnabled)
    {
        getModuleController()->toggleBlink(_buf_container_x, _buf_container_y);
        toggleBlinkTime = millis();
    }
}

void SetContainerMenu::display(){
    lcd->printLines(menuLine1(),menuLine2(),menuLine3(),menuLine4());
    pointer_position = minPointerPosition();
    lcd->setPointerInLine(minPointerPosition());
    printContainerTime(_buf_container_x,_buf_container_y);
}

void SetContainerMenu::onEnter(MenuController *m)
{
    _enter_count++;
    
    if(_enter_count == 0x1)
    {
        dateMenu = new SetDateSettingsMenu(getLCD(),getRTC(),getModuleController());
        dateMenu->display();
    }
    else if(_enter_count >= 0x2 && _enter_count <= 0x4)
    {
        dateMenu->_enter_count++;
    }
    else if(_enter_count == 0x5)
    {
        _buf_year = dateMenu->_buf_year;
        _buf_month = dateMenu->_buf_month;
        _buf_day = dateMenu->_buf_day;
        
        timeMenu = new SetTimeMenu(getLCD(),getRTC(),getModuleController());
        timeMenu->display();
    }
    else if(_enter_count >= 0x6 && _enter_count <= 0x7)
    {
        timeMenu->_enter_count++;
    }
    else if(_enter_count == 0x8)
    {
        _buf_hour = timeMenu->_buf_hour;
        _buf_minute = timeMenu->_buf_minute;
        
        execute_time time;
        
        time.year = _buf_year;
        time.month = _buf_month;
        time.day = _buf_day;
        time.hour = _buf_hour;
        time.minute = _buf_minute;
        
        getModuleController()->containers[_buf_container_x][_buf_container_y].time = time;
        getModuleController()->containers[_buf_container_x][_buf_container_y].executed = false;
        blinkEnabled = false;
        getModuleController()->setContainerStatus(_buf_container_x,_buf_container_y,0x0);
        
        delete timeMenu;
        delete dateMenu;
        
        MainMenu *newMenu = new MainMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }
}