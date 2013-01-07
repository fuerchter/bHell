#ifndef CONFIG
#define CONFIG

#include <map>
#include <fstream>
using namespace std;

#include "SettingCategory.h"

class Config
{
public:
	bool doesCategoryExist(SettingCategory category);
	SettingCategory readCategory(SettingCategory category);
	SettingCategory getCategory(SettingCategory category);
	void removeCategory(SettingCategory category);
	void writeCategory(SettingCategory category);
	
	string readLine();
	void writeLine();
};

#endif