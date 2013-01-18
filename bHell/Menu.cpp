#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(GameState state):
currNo_(0)
{
	if(state==GameStates::Menu)
	{
		title_="Menu";
		elements_.push_back(MenuElement("Start", GameStates::Start));
		elements_.push_back(MenuElement("Options", GameStates::Options));
		elements_.push_back(MenuElement("Quit", GameStates::Quit));
		escAction_=GameStates::Quit;
	}
	else if(state==GameStates::Options)
	{
		title_="Options";
		elements_.push_back(MenuElement("Video", GameStates::Video));
		elements_.push_back(MenuElement("Controls", GameStates::Controls));
		escAction_=GameStates::Menu;
	}
	else
	{

	}
}

Menu::Menu(GameState state, GameState escAction, SettingCategory category):
currNo_(0), escAction_(escAction)
{
	title_=category.getTitle();
	for(int i=0; i<category.getSeSize(); i++)
	{
		elements_.push_back(MenuElement(category.getSetting(i).getTitle(), state, new Setting(category.getSetting(i))));
	}
}

Menu::Menu(string title, GameState escAction, vector<MenuElement> elements):
title_(title), currNo_(0), escAction_(escAction), elements_(elements)
{

}


void Menu::goUp()
{
	currNo_--;
	if(currNo_<0)
	{
		currNo_=elements_.size()-1;
	}
}

void Menu::goDown()
{
	currNo_++;
	if(currNo_>elements_.size()-1)
	{
		currNo_=0;
	}
}

GameState Menu::enter()
{
	return elements_[currNo_].getAction();
}

GameState Menu::escape()
{
	return escAction_;
}

int Menu::getCurrNo()
{
	return currNo_;
}

string Menu::getTitle()
{
	return title_;
}


MenuElement Menu::getEl(int i)
{
	return elements_[i];
}

MenuElement Menu::getCurrEl()
{
	return elements_[currNo_];
}

bool Menu::hasCurrSetting()
{
	return elements_[currNo_].hasSetting();
}

Setting *Menu::getCurrSetting()
{
	if(hasCurrSetting())
	{
		return elements_[currNo_].getSetting();
	}
	else
	{
		return NULL;
	}
}

vector<string> Menu::getElTitles()
{
	vector<string> titles;
	for(int i=0; i<elements_.size(); i++)
	{
		titles.push_back(elements_[i].getTitle());
	}
	return titles;
}

vector<sf::Text> Menu::constructText(sf::Font &font, int vSpacing, sf::Color normal, sf::Color hover)
{
	vector<string> titles=getElTitles();
	vector<sf::Text> texts;
	for(int i=0; i<titles.size(); i++)
	{
		if(getEl(i).hasSetting())
		{
			titles[i]+=" " +getEl(i).getSetting()->getAttribute();
		}
		texts.push_back(sf::Text(titles[i], font));

		texts[i].setPosition(0, i*vSpacing);

		if(getCurrNo()==i)
		{
			texts[i].setColor(hover);
		}
		else
		{
			texts[i].setColor(normal);
		}
	}
	return texts;
}


string Menu::getCurrAtt()
{
	if(hasCurrSetting())
	{
		return elements_[currNo_].getSetting()->getAttribute();
	}
	else
	{
		return NULL;
	}
}

void Menu::setCurrAtt(string attribute)
{
	if(hasCurrSetting())
	{
		elements_[currNo_].getSetting()->setAttribute(attribute);
	}
}

Setting::Type Menu::getCurrType()
{
	if(hasCurrSetting())
	{
		return elements_[currNo_].getSetting()->getType();
	}
	else
	{
		return Setting::Error;
	}
}


SettingCategory Menu::constructCat()
{
	vector<Setting> settings;
	for(int i=0; i<elements_.size(); i++)
	{
		if(elements_[i].hasSetting())
		{
			settings.push_back(Setting(elements_[i].getSetting()->getTitle(), elements_[i].getSetting()->getAttribute(), elements_[i].getSetting()->getType()));
		}
	}
	return SettingCategory(title_, settings);
}
