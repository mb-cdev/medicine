#include <AlarmMenu.h>
#include <MenuController.h>

void AlarmMenu::onRefresh(MenuController *m)
{
    if(!lastAlertVisible || millis() - lastAlertVisible >= 800)
    {
        if(!alertVisible){
            getLCD()->printLines(menuLine1(), menuLine2(),menuLine3(), menuLine4());
            alertVisible = true;
        }else{
            alertVisible = false;
            getLCD()->printLines(menuLine1(), menuLine1(),menuLine3(), menuLine4());
        }
        lastAlertVisible = millis();
    }
}

void AlarmMenu::onEnter(MenuController *m)
{
    getModuleController()->resetExecutedContainers();
    MainMenu *newMenu = new MainMenu(getLCD(),getRTC(),getModuleController());
    m->setNewMenuObject(newMenu);
}