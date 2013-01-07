#ifndef SETTING
#define SETTING

#include <string>
#include <sstream>
using namespace std;

#include "SettingTypes.h"
using SettingTypes::SettingType;

class Setting
{
public:
	Setting(string title, string attribute, SettingType type);
	string getTitle();
	string getAttribute();
	//Returns -1 if Setting was not of type int and 0 if it was type int but attribute was not
	int getAttInt();
	bool getAttBool();
	void setAttribute(string attribute);
	void toggleBool();
	SettingType getType();
	
private:
	string title_;
	string attribute_;
	SettingType type_;
};

#endif