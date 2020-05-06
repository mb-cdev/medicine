#ifndef MODULE_CONTROLLER_INZ
#define MODULE_CONTROLLER_INZ

#include <Globals.h>
#include <DateRTC.h>
#include <LCD.h>

class MenuController;

class ModuleController{
    
    DateRTC *dRTC;
    LCD *lcd;
    
    char _buf_test_module_x = 0x0;
    char _buf_test_module_y = 0x0;
    
    bool alarm = false;
   
public:

    bool alarmEnabled = false;
    
    struct module modules[2][MAX_MODULES];
                          //0=X, 1=Y
    struct container containers[MAX_MODULES][MAX_MODULES];                               
                          //X         //Y                    
    void init();
    char *checkForNewModule(MODULE_AXIS);
    void toggleBlink(char,char);
    bool isAddressUsed(char);
    char addNewModule(char,char);
    ModuleController(DateRTC*,LCD*);
    char setModuleStatus(char,char);
    char getModuleStatus(char);
    void setContainerStatus(char,char,char);
    void listen(MenuController*);
    void setAllContainerToStatus(char);
    unsigned long int timeToInt(char,char,char,char,char);
    void resetExecutedContainers();
};

#endif