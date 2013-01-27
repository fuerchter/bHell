#ifndef SETTINGCATEGORY
#define SETTINGCATEGORY

#include <vector>

#include "SFML\Window.hpp"

#include "Setting.h"

using namespace std;

class SettingCategory
{
public:
	SettingCategory(string title, vector<Setting> settings);
	string getTitle();
	bool isEmpty();
	Setting getSetting(int index);
	//Searches setting via title, returns setting with type Error if it was not found
	Setting getSetting(string title);
	void setSetting(int index, Setting setting);
	int getSeSize();
private:
	string title_;
	//no map because we need to iterate through
	vector<Setting> settings_;
};

#endif