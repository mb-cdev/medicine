#include <ModuleController.h>
#include <stdio.h>
#include <MenuController.h>
#include <AlarmMenu.h>

unsigned long int ModuleController::timeToInt(char year, char month, char day, char hour, char minute)
{
    unsigned long int time = 0;
    
    time += ((unsigned long int)year) * 31536000UL;
    time += ((unsigned long int)month) * 2592000UL;
    time += ((unsigned long int)day) * 86400UL;
    time += ((unsigned long int)hour) * 3600UL;
    time += ((unsigned long int)minute)* 60UL;
    
    return time;
}

void ModuleController::init(){
}

ModuleController::ModuleController(DateRTC *d, LCD *l){
    dRTC = d;
    lcd = l;
}

char *ModuleController::checkForNewModule(MODULE_AXIS axis)
{
    char _temp_axis_index = 0x0;
    char response = 0x0;
    
    if(axis == MODULE_AXIS::X){
        _temp_axis_index = 0x0;
    }else if(axis == MODULE_AXIS::Y){
        _temp_axis_index = 0x1;
    }
    
    for(char i = 1; i<127; i++)
    {
        Wire.beginTransmission(i);
        response = Wire.endTransmission();
        
        if(response == 0x0
           && !isAddressUsed(i))
        {
            return addNewModule(i, _temp_axis_index);
        }
    }
    
    return 0x0; //NOTHING
}

char ModuleController::addNewModule(char address, char axis)
{
    for(int i = 0; i<=MAX_MODULES-1;i++)
    {
        if(modules[axis][i].address == 0x0)
        {
            modules[axis][i].address = address;
            
            setModuleStatus(modules[axis][i].address, 0x0);
            
            if(axis == 0x0)
            {
                for(int j = 0; j<=MAX_MODULES-1;j++)
                {
                    containers[i][j].module_address_x = address;
                }
            }
            else if(axis == 0x1)
            {
                for(int j = 0; j<=MAX_MODULES-1;j++)
                {
                    containers[j][i].module_address_y = address;
                }
            }
            
            return 0x1; // address added
        }
    }
    
    return 0x2; //no free address
}

bool ModuleController::isAddressUsed(char address)
{
    if(address == dRTC->getI2CAddress()){
        return true;
    }
    if(address == 0x57){
        return true; //reserved adress
    }
    
    for(int axis = 0; axis <= 1; axis++)
    {
        for(int j = 0; j<=MAX_MODULES-1; j++)
        {
            if(modules[axis][j].address == address)
            {
                return true;
            }
        }
    }
    
    return false;
}

void ModuleController::toggleBlink(char container_x, char container_y)
{
    char address_x = containers[container_x][container_y].module_address_x;
    char address_y = containers[container_x][container_y].module_address_y;
    
    char status_x = getModuleStatus(address_x);
    char status_y = getModuleStatus(address_y);
    
    bool newStatus = !(status_x & status_y);
    
    setModuleStatus(address_x, newStatus);
    setModuleStatus(address_y, newStatus);
}

void ModuleController::setContainerStatus(char container_x, char container_y, char status)
{
    char address_x = containers[container_x][container_y].module_address_x;
    char address_y = containers[container_x][container_y].module_address_y;
    
    bool newStatus = status;
    
    setModuleStatus(address_x, newStatus);
    setModuleStatus(address_y, newStatus);
}

char ModuleController::getModuleStatus(char address)
{
    Wire.requestFrom(address, 1);
    if(Wire.available()){
        return (char)Wire.read();
    }
    
    return 0x0;
}

char ModuleController::setModuleStatus(char address, char status)
{
    Wire.beginTransmission(address);
    Wire.write(status);
    return Wire.endTransmission();
}

void ModuleController::setAllContainerToStatus(char status)
{
    for(int i=0; i<=MAX_MODULES-1;i++)
    {
        for(int j=0; j<=MAX_MODULES-1;j++)
        {
            char address_x = containers[i][j].module_address_x;
            char address_y = containers[i][j].module_address_y;
            
            setModuleStatus(address_x, status);
            setModuleStatus(address_y, status);
        }
    }
}

void ModuleController::resetExecutedContainers()
{
    execute_time time;
    for(int i=0;i<=MAX_MODULES-1;i++)
    {
        for(int j=0;j<=MAX_MODULES-1;j++)
        {
            if(containers[i][j].executed)
            {
                containers[i][j].time = time;
                containers[i][j].executed = false;
                setContainerStatus(i,j,0x0);
            }
        }
    }
}

void ModuleController::listen(MenuController *m)
{
    _buf_test_module_x++;
    
    if(_buf_test_module_x > (MAX_MODULES - 1))
    {        
        _buf_test_module_y++;
        if(_buf_test_module_y > (MAX_MODULES - 1)){
            _buf_test_module_y = 0x0;
        }
        _buf_test_module_x = 0x0;
    }
    
    unsigned long int currentInt = timeToInt(
        dRTC->currentDate.year,
        dRTC->currentDate.month,
        dRTC->currentDate.day,
        dRTC->currentDate.hour,
        dRTC->currentDate.minute
    );
    
    unsigned long int containerInt = timeToInt(
        containers[_buf_test_module_x][_buf_test_module_y].time.year,
        containers[_buf_test_module_x][_buf_test_module_y].time.month,
        containers[_buf_test_module_x][_buf_test_module_y].time.day,
        containers[_buf_test_module_x][_buf_test_module_y].time.hour,
        containers[_buf_test_module_x][_buf_test_module_y].time.minute
    );
    
    if(containerInt && currentInt >= containerInt
       && !containers[_buf_test_module_x][_buf_test_module_y].executed)
    {
        setContainerStatus(_buf_test_module_x,_buf_test_module_y,0x1);
        containers[_buf_test_module_x][_buf_test_module_y].executed = true;
        alarm = true;
    }
     
    if(alarm)
    {
        AlarmMenu *newMenu = new AlarmMenu(m->menu->getLCD(), m->menu->getRTC(), m->menu->getModuleController());
        m->setNewMenuObject(newMenu);
        alarm = false;
    }
}