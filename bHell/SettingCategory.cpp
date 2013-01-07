#include "SettingCategory.h"

SettingCategory::SettingCategory(string title):
title_(title)
{
	if(title_=="Video")
	{
		sf::VideoMode desktop=sf::VideoMode::getDesktopMode();
		stringstream width;
		width << desktop.width;
		stringstream height;
		height << desktop.height;
		settings_.push_back(Setting("Width", width.str(), SettingTypes::Int));
		settings_.push_back(Setting("Height", height.str(), SettingTypes::Int));
		settings_.push_back(Setting("VSync", "0", SettingTypes::Bool));
		settings_.push_back(Setting("Framecap", "60", SettingTypes::Int));
		settings_.push_back(Setting("Windowed", "0", SettingTypes::Bool));
		settings_.push_back(Setting("Show FPS", "0", SettingTypes::Bool));
	}
	else if(title_=="Controls")
	{
		settings_.push_back(Setting("Up", "Keyboard_Up", SettingTypes::Input));
		settings_.push_back(Setting("Down", "Keyboard_Down", SettingTypes::Input));
		settings_.push_back(Setting("Left", "Keyboard_Left", SettingTypes::Input));
		settings_.push_back(Setting("Right", "Keyboard_Right", SettingTypes::Input));
		settings_.push_back(Setting("Enter", "Keyboard_Return", SettingTypes::Input));
		settings_.push_back(Setting("Back", "Keyboard_Escape", SettingTypes::Input));
	}
	else
	{

	}
}

SettingCategory::SettingCategory(string title, vector<Setting> settings):
title_(title), settings_(settings)
{

}

string SettingCategory::getTitle()
{
	return title_;
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
	return Setting("null", "0", SettingTypes::Error);
}

int SettingCategory::getSeSize()
{
	return settings_.size();
}