#include <MenuCore.h>

MenuCore::MenuCore(LCD *l, DateRTC *d, ModuleController *mc){
    lcd = l;
    dRTC = d;
    moduleController = mc;
}

void MenuCore::pointerUp(){
    pointer_position--;
    if(pointer_position < minPointerPosition()){
        pointer_position = maxPointerPosition();
    }
    setPointerOnScreen();
}
    
void MenuCore::pointerDown(){
    pointer_position++;
    if(pointer_position > maxPointerPosition()){
        pointer_position = minPointerPosition();
    }
    setPointerOnScreen();
}

void MenuCore::setPointerOnScreen(){
    char pp = pointer_position;
    lcd->setPointerInLine(pp);
}

void MenuCore::onEnter(MenuController *m){}
void MenuCore::onUp(MenuController *m){}
void MenuCore::onDown(MenuController *m){}
void MenuCore::onRefresh(MenuController *m){}

void MenuCore::display(){
    lcd->printLines(menuLine1(),menuLine2(),menuLine3(),menuLine4());
    pointer_position = minPointerPosition();
    lcd->setPointerInLine(minPointerPosition());
}

LCD *MenuCore::getLCD(){
    return lcd;
}
DateRTC *MenuCore::getRTC(){
    return dRTC;
}
ModuleController *MenuCore::getModuleController(){
    return moduleController;
}