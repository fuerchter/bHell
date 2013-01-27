#include "SettingCategory.h"

SettingCategory::SettingCategory(string title, vector<Setting> settings):
title_(title), settings_(settings)
{

}

string SettingCategory::getTitle()
{
	return title_;
}

bool SettingCategory::isEmpty()
{
	return settings_.empty();
}

Setting SettingCategory::getSetting(int index)
{
	return settings_[index];
}

Setting SettingCategory::getSetting(string title)
{
	for(int i=0; i<getSeSize(); i++)
	{
		if(settings_[i].getTitle()==title)
		{
			return settings_[i];
		}
	}
	return Setting("null", "0", Setting::Error);
}

void SettingCategory::setSetting(int index, Setting setting)
{
	settings_[index]=setting;
}

int SettingCategory::getSeSize()
{
	return settings_.size();
}