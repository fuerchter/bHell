#ifndef SETTINGCATEGORY
#define SETTINGCATEGORY

#include <vector>

#include "SFML\Window.hpp"

#include "Setting.h"

using namespace std;

class SettingCategory
{
public:
	//Uses preset titles to create categories, settings vector is uninitialized if parameter title doesn't match a preset
	SettingCategory(string title);
	SettingCategory(string title, vector<Setting> settings);
	string getTitle();
	bool isEmpty();
	Setting getSetting(int index);
	//Searches setting via title, returns setting with type Error if it was not found
	Setting getSetting(string title);
	int getSeSize();
private:
	string title_;
	//no map because we need to iterate through
	vector<Setting> settings_;
};

#endif