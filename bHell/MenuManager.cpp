#include "MenuManager.h"

MenuManager::MenuManager(GameState state, map<GameState, Menu> menus):
state_(state), currAttribute_("")
{
	font_.loadFromFile("arial.ttf");
	
	menus_=menus;
	//extracts each SettingCategory from config (in case the given Category is in the config)
	for(map<GameState, Menu>::iterator it=menus_.begin(); it!=menus_.end(); it++)
	{
		Menu te=it->second;
		SettingCategory t=te.constructCat();
		t=Config::getCategory(t);
		//if the extracted Category is empty the Menu stays the same
		if(t.getSeSize()==0)
		{

		}
		else
		{
			it->second=Menu(it->first, te.escape(), t);
		}
	}

	input_=ControlManager(menus_[GameStates::Controls].constructCat());

	menu_=menus_[state];
	texts_=constructText();
}

GameState MenuManager::update(sf::Event currentEvent)
{
	if(change_==Setting::Int)
	{
		//current attribute has to contain anything to be able to be saved to config
		if((input_.getControl("Enter")->menuButtonPressed(currentEvent) || input_.getControl("Enter")->axisMoved()) && !currAttribute_.empty())
		{
			menu_.setCurrAtt(currAttribute_);
			changeSetting(change_);
		}
		if(currentEvent.type==sf::Event::TextEntered)
		{
			char current=currentEvent.text.unicode;
			if(isdigit(current))
			{
				currAttribute_+=current;
				menu_.setCurrAtt(currAttribute_);
			}
		}
	}
	else if(change_==Setting::Input)
	{
		if(currentEvent.type==sf::Event::KeyPressed)
		{
			menu_.setCurrAtt("Keyboard_" +thor::toString(currentEvent.key.code));
			changeSetting(change_);
		}
		else if(currentEvent.type==sf::Event::MouseButtonPressed)
		{
			menu_.setCurrAtt("MouseButton_" +thor::toString(currentEvent.mouseButton.button));
			changeSetting(change_);
		}
		else if(currentEvent.type==sf::Event::JoystickButtonPressed)
		{
			string temp="JoystickButton_";
			stringstream convert;
			convert << currentEvent.joystickButton.joystickId;
			temp+=convert.str();
			temp+="_";
			stringstream convert2;
			convert2 << currentEvent.joystickButton.button;
			temp+=convert2.str();

			menu_.setCurrAtt(temp);

			changeSetting(change_);
		}
		else if(currentEvent.type==sf::Event::JoystickMoved && (currentEvent.joystickMove.position>50 || currentEvent.joystickMove.position<-50))
		{
			string temp="Joystick_";
			stringstream convert;
			convert << currentEvent.joystickButton.joystickId;
			temp+=convert.str();
			temp+="_";
			temp+=thor::toString(currentEvent.joystickMove.axis);
			temp+="_";
			if(currentEvent.joystickMove.position>0)
			{
				temp+="1";
			}
			else
			{
				temp+="-1";
			}

			menu_.setCurrAtt(temp);

			changeSetting(change_);
		}
	}
	else if(input_.getControl("Up")->menuButtonPressed(currentEvent) || input_.getControl("Up")->axisMoved())
	{
		menu_.goUp();
	}
	else if(input_.getControl("Down")->menuButtonPressed(currentEvent) || input_.getControl("Down")->axisMoved())
	{
		menu_.goDown();
	}
	else if(input_.getControl("Enter")->menuButtonPressed(currentEvent) || input_.getControl("Enter")->axisMoved())
	{
		//causes change status
		if(menu_.hasCurrSetting())
		{
			if(menu_.getCurrType()==Setting::Int)
			{
				change_=Setting::Int;
				currAttribute_="";
			}
			else if(menu_.getCurrType()==Setting::Bool)
			{
				menu_.getCurrSetting()->toggleBool();
				change_=Setting::Bool;
				changeSetting(change_);
			}
			else if(menu_.getCurrType()==Setting::Input)
			{
				change_=Setting::Input;
			}
		}
		else
		{
			state_=menu_.enter();
			menu_=menus_[state_];
		}
	}
	else if(input_.getControl("Back")->menuButtonPressed(currentEvent) || input_.getControl("Back")->axisMoved())
	{
		state_=menu_.escape();
		menu_=menus_[state_];
	}
	return state_;
}

vector<sf::Text> MenuManager::constructText(int vSpacing, sf::Color normal, sf::Color hover)
{
	return menu_.constructText(font_, vSpacing, normal, hover);
}

SettingCategory MenuManager::getCategory(GameState state)
{
	vector<GameState>::iterator it=std::find(changed_.begin(), changed_.end(), state);
	if(it != changed_.end())
	{
		changed_.erase(it);
	}
	return menus_[state].constructCat();
}

bool MenuManager::categoryChanged(GameState state)
{
	if(std::find(changed_.begin(), changed_.end(), state) != changed_.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MenuManager::changeSetting(Setting::Type type)
{
	change_=Setting::Error;
	Config::writeCategory(menu_.constructCat());
	if(std::find(changed_.begin(), changed_.end(), state_) == changed_.end())
	{
		changed_.push_back(state_);
	}

	if(type==Setting::Input)
	{
		input_=ControlManager(menu_.constructCat());
	}
}