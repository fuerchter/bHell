#include "Control.h"

Control::Control()
{
	type_=Error;
}

Control::Control(Setting setting):
threshold_(50), sensitivity_(50)
{
	string temp=setting.getAttribute();
	size_t pos=temp.find("_");
	string attribute=temp.substr(pos+1);
	temp.resize(pos);
	string type=temp;
	if(type=="Keyboard")
	{
		type_=Keyboard;
		key_=thor::toKeyboardKey(attribute);
	}
	else if(type=="MouseButton")
	{
		type_=MouseButton;
		mouseButton_=thor::toMouseButton(attribute);
	}
	else if(type=="JoystickButton")
	{
		type_=JoystickButton;
		size_t pos2=attribute.find("_");
		string button=attribute.substr(pos2+1);
		attribute.resize(pos2);
		stringstream convert(attribute);
		if(!(convert >> joystick_))
		{
			joystick_=-1;
		}
		stringstream convert2(button);
		if(!(convert2 >> joystickButton_))
		{
			joystickButton_=-1;
		}
	}
	else if(type=="Joystick")
	{
		type_=Joystick;
		size_t pos2=attribute.find("_");
		string axis=attribute.substr(pos2+1);
		attribute.resize(pos2);
		stringstream convert(attribute);
		if(!(convert >> joystick_))
		{
			joystick_=-1;
		}
		size_t pos3=axis.find("_");
		string direction=axis.substr(pos3+1);
		axis.resize(pos3);
		joystickAxis_=thor::toJoystickAxis(axis);
		stringstream convert2(direction);
		if(!(convert2 >> joystickDirection_))
		{
			joystick_=0;
		}
		lastJoystickPosition_=0;
	}
}

void Control::setSensitivity(int sensitivity)
{
	sensitivity_=sensitivity;
}

float Control::axisPosition()
{
	float position=0;
	if(type_==Joystick)
	{
		position=sf::Joystick::getAxisPosition(joystick_, joystickAxis_)*joystickDirection_;
		//scaling with sensitivity
		position=position*(100/(100-(float)sensitivity_));
		if(position>100)
		{
			position=100;
		}
		if(position<0)
		{
			position=0;
		}
	}
	return position;
}

void Control::setThreshold(int threshold)
{
	if(threshold<0)
	{
		threshold*=(-1);
	}
	threshold_=threshold;
}

bool Control::axisMoved()
{
	int position=0;
	if(type_==Joystick)
	{
		position=(int)(sf::Joystick::getAxisPosition(joystick_, joystickAxis_)*joystickDirection_);
		//axis passed threshold
		if(position>threshold_ && lastJoystickPosition_<=threshold_)
		{
			lastJoystickPosition_=(float)position;
			if(position!=0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			lastJoystickPosition_=(float)position;
			return 0;
		}
	}
	lastJoystickPosition_=0;
	return 0;
}

bool Control::buttonPressed()
{
	if(type_==Keyboard)
	{
		if(sf::Keyboard::isKeyPressed(key_))
		{
			return true;
		}
	}
	else if(type_==MouseButton)
	{
		if(sf::Mouse::isButtonPressed(mouseButton_))
		{
			return true;
		}
	}
	else if(type_==JoystickButton)
	{
		if(sf::Joystick::isButtonPressed(joystick_, joystickButton_))
		{
			return true;
		}
	}
	return false;
}

bool Control::menuButtonPressed(sf::Event currentEvent)
{
	if(type_==Keyboard)
	{
		if(currentEvent.type==sf::Event::KeyPressed && currentEvent.key.code==key_)
		{
			return true;
		}
	}
	else if(type_==MouseButton)
	{
		if(currentEvent.type==sf::Event::MouseButtonPressed && currentEvent.mouseButton.button==mouseButton_)
		{
			return true;
		}
	}
	else if(type_==JoystickButton)
	{
		if(currentEvent.type==sf::Event::JoystickButtonPressed && currentEvent.joystickButton.joystickId==joystick_ && currentEvent.joystickButton.button==joystickButton_)
		{
			return true;
		}
	}
	return false;
}