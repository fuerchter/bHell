#include "GameMenu.h"

GameMenu::GameMenu(GameState state):
state_(state), menu_(state), font_(), video_("Video"), controls_("Controls"), input_(controls_), changeInt_(false), currAttribute_(""), changeInput_(false), videoChanged_(false)
{
	font_.loadFromFile("arial.ttf");
	video_=config_.getCategory(video_);
	controls_=config_.getCategory(controls_);
	input_=ControlManager(controls_);
	if(state==GameStates::Video)
	{
		menu_=Menu(state, GameStates::Options, video_);
	}
	else if(state==GameStates::Controls)
	{
		menu_=Menu(state, GameStates::Options, controls_);
	}
	else
	{
		menu_=Menu(state);
	}
	texts_=constructText();
}

GameState GameMenu::update(sf::Event currentEvent)
{
	if(changeInt_)
	{
		//current attribute has to contain anything to be able to be saved to config
		if((input_.getControl("Enter")->menuButtonPressed(currentEvent) || input_.getControl("Enter")->axisMoved()) && !currAttribute_.empty())
		{
			changeInt_=false;
			menu_.setCurrAtt(currAttribute_);
			if(state_==GameStates::Video)
			{
				videoChanged_=true;
				video_=menu_.constructCat();
				config_.writeCategory(video_);
			}
		}
		if(currentEvent.type==sf::Event::TextEntered)
		{
			char current=currentEvent.text.unicode;
			if(isdigit(current))
			{
				currAttribute_+=current;
			}
		}
	}
	else if(changeInput_)
	{
		if(currentEvent.type==sf::Event::KeyPressed)
		{
			menu_.setCurrAtt("Keyboard_" +thor::toString(currentEvent.key.code));
			controlsChanged();
		}
		else if(currentEvent.type==sf::Event::MouseButtonPressed)
		{
			menu_.setCurrAtt("MouseButton_" +thor::toString(currentEvent.mouseButton.button));
			controlsChanged();
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

			controlsChanged();
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

			controlsChanged();
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
		if(menu_.hasCurrSetting())
		{
			if(menu_.getCurrType()==Setting::Int)
			{
				changeInt_=true;
				currAttribute_="";
			}
			else if(menu_.getCurrType()==Setting::Bool)
			{
				menu_.getCurrSetting()->toggleBool();
				if(state_==GameStates::Video)
				{
					videoChanged_=true;
					video_=menu_.constructCat();
					config_.writeCategory(video_);
				}
			}
			else if(menu_.getCurrType()==Setting::Input)
			{
				changeInput_=true;
			}
		}
		else
		{
			GameState next=menu_.enter();
			if(next==GameStates::Video)
			{
				menu_=Menu(next, state_, video_);
			}
			else if(next==GameStates::Controls)
			{
				menu_=Menu(next, state_, controls_);
			}
			else
			{
				menu_=Menu(next);
			}
			state_=next;
		}
	}
	else if(input_.getControl("Back")->menuButtonPressed(currentEvent) || input_.getControl("Back")->axisMoved())
	{
		GameState prev=menu_.escape();
		if(prev==GameStates::Video)
		{
			menu_=Menu(prev, state_, video_);
		}
		else if(prev==GameStates::Controls)
		{
			menu_=Menu(prev, state_, controls_);
		}
		else
		{
			menu_=Menu(prev);
		}
		state_=prev;
	}
	input_.getControl("Left")->axisPosition();
	return state_;
}

//NEEDS COLOR PROPERTIES
vector<sf::Text> GameMenu::constructText(int vSpacing, sf::Color normal, sf::Color hover)
{
	return menu_.constructText(font_, vSpacing, normal, hover);
}

SettingCategory GameMenu::getVideo()
{
	videoChanged_=false;
	return video_;
}

SettingCategory GameMenu::getControls()
{
	return controls_;
}

bool GameMenu::videoChanged()
{
	return videoChanged_;
}

void GameMenu::controlsChanged()
{
	changeInput_=false;
	controls_=menu_.constructCat();
	config_.writeCategory(controls_);
	input_=ControlManager(controls_);
}