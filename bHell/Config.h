#ifndef CONFIG
#define CONFIG

#include <map>
#include <fstream>
using namespace std;

#include "SettingCategory.h"

class Config
{
public:
	static bool doesCategoryExist(SettingCategory category);
	static SettingCategory readCategory(SettingCategory category);
	static SettingCategory getCategory(SettingCategory category);
	static void removeCategory(SettingCategory category);
	static void writeCategory(SettingCategory category);
};

#endif