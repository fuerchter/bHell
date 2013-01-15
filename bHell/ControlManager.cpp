#include "ControlManager.h"

ControlManager::ControlManager()
{

}

ControlManager::ControlManager(SettingCategory settings)
{
	for(int i=0; i<settings.getSeSize(); i++)
	{
		controls_.insert(pair<string, Control>(settings.getSetting(i).getTitle(), Control(settings.getSetting(i))));
	}
}

Control *ControlManager::getControl(string name)
{	
	return &controls_[name];
}