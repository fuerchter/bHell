#ifndef CONTROLMANAGER
#define CONTROLMANAGER

#include <map>

#include "SettingCategory.h"
#include "Control.h"

class ControlManager
{
public:
	ControlManager();
	ControlManager(SettingCategory settings);

	Control *getControl(string name);
private:
	map<string, Control> controls_;
};

#endif