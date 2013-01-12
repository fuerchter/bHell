#ifndef CONTROL
#define CONTROL

#include <iostream>
using namespace std;

#include "SFML\Window.hpp"
#include "Thor\Events\InputNames.hpp"

#include "Setting.h"

class Control
{
public:
	enum Type
	{
		Error, Keyboard, MouseButton, JoystickButton, Joystick
	};

	//Writes Error into type
	Control();
	Control(Setting setting);

	void setSensitivity(int sensitivity);
	//gets current position dependent from this Control's sensitivity
	float axisPosition();
	void setThreshold(int threshold);
	bool axisMoved();
	bool buttonPressed();
	bool menuButtonPressed(sf::Event currentEvent);
private:
	//type is no enum because it has to be read out from the config
	Type type_;
	sf::Keyboard::Key key_;
	sf::Mouse::Button mouseButton_;
	int joystick_;
	int joystickButton_;
	sf::Joystick::Axis joystickAxis_;
	int joystickDirection_;
	float lastJoystickPosition_;
	int threshold_;
	int sensitivity_;
};

#endif