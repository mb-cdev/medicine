#include <AddNewXYModuleMenu.h>
#include <MenuController.h>

void AddNewXYModuleMenu::onUp(MenuController *m){
    _buf_axis++;
    if(_buf_axis > 1){
        _buf_axis = 0;
    }
    
    switch(_buf_axis){
        case 0x0:
            current_axis = MODULE_AXIS::X;
        break;
        case 0x1:
            current_axis = MODULE_AXIS::Y;
        break;
            
    }
    m->menu->lcd->print(MODULE_AXIS_NAMES[_buf_axis],0x2);
}

void AddNewXYModuleMenu::onDown(MenuController *m)
{
    _buf_axis--;
    if(_buf_axis < 0){
        _buf_axis = 1;
    }
    
    switch(_buf_axis){
        case 0x0:
            current_axis = MODULE_AXIS::X;
        break;
        case 0x1:
            current_axis = MODULE_AXIS::Y;
        break;
            
    }
    m->menu->getLCD()->print(MODULE_AXIS_NAMES[_buf_axis],0x2);
}

void AddNewXYModuleMenu::onRefresh(MenuController *m)
{
    switch((int)getModuleController()->checkForNewModule(current_axis)){
        case 0x1:
            m->menu->getLCD()->printLines("",addressAddedLine,"", enterToContinue);
        break;
        case 0x2:
            m->menu->getLCD()->printLines("",addressNotAddedLine,"", enterToContinue);
        break;
    }
}

void AddNewXYModuleMenu::onEnter(MenuController *m)
{
    MainMenu *newMenu = new MainMenu(getLCD(), getRTC(),getModuleController());
    m->setNewMenuObject(newMenu);
}