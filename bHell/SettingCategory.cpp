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
		settings_.push_back(Setting("Width", width.str(), Setting::Int));
		settings_.push_back(Setting("Height", height.str(), Setting::Int));
		settings_.push_back(Setting("VSync", "0", Setting::Bool));
		settings_.push_back(Setting("Framecap", "60", Setting::Int));
		settings_.push_back(Setting("Windowed", "0", Setting::Bool));
		settings_.push_back(Setting("Show FPS", "0", Setting::Bool));
	}
	else if(title_.find("Controls")==0)
	{
		settings_.push_back(Setting("Up", "Keyboard_Up", Setting::Input));
		settings_.push_back(Setting("Down", "Keyboard_Down", Setting::Input));
		settings_.push_back(Setting("Left", "Keyboard_Left", Setting::Input));
		settings_.push_back(Setting("Right", "Keyboard_Right", Setting::Input));
		settings_.push_back(Setting("Enter", "Keyboard_Return", Setting::Input));
		settings_.push_back(Setting("Back", "Keyboard_Escape", Setting::Input));
	}
	else if(title_=="Menu Controls")
	{
		settings_.push_back(Setting("Up", "Keyboard_Up", Setting::Input));
		settings_.push_back(Setting("Down", "Keyboard_Down", Setting::Input));
		settings_.push_back(Setting("Left", "Keyboard_Left", Setting::Input));
		settings_.push_back(Setting("Right", "Keyboard_Right", Setting::Input));
		settings_.push_back(Setting("Enter", "Keyboard_Return", Setting::Input));
		settings_.push_back(Setting("Back", "Keyboard_Escape", Setting::Input));
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