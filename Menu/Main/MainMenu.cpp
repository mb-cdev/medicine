#include <MainMenu.h>
#include <MenuController.h>
#include <stdio.h>

void MainMenu::onEnter(MenuController *m){
    if(pointer_position == 3){
        SetDateMenu *newMenu = new SetDateMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }else if(pointer_position == 4){
        AddNewXYModuleMenu *newMenu = new AddNewXYModuleMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }else if(pointer_position == 2){
        SetContainerMenu *newMenu = new SetContainerMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }
}
void MainMenu::onUp(MenuController *m){
    pointerUp();
}
void MainMenu::onDown(MenuController *m){
    pointerDown();
}
void MainMenu::onRefresh(MenuController *m){
    
    if(!time || millis() - time >= 15000)
    {
        lcd->print(dRTC->getDateInASCII(),0x1);
        time = millis();
    }
}
