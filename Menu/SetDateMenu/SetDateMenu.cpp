#include <SetDateMenu.h>
#include <MenuController.h>
#include <SetTimeMenu.h>
#include <SetDateSettingsMenu.h>

void SetDateMenu::onUp(MenuController *m){
    pointerUp();
}
void SetDateMenu::onDown(MenuController *m){
    pointerDown();
}
void SetDateMenu::onEnter(MenuController *m)
{
    if(pointer_position == 4)
    {
        MainMenu *newMenu = new MainMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }
    else if(pointer_position == 2)
    {
        SetTimeMenu *newMenu = new SetTimeMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }
    else if(pointer_position == 3)
    {
        SetDateSettingsMenu *newMenu = new SetDateSettingsMenu(getLCD(), getRTC(), getModuleController());
        m->setNewMenuObject(newMenu);
    }
}