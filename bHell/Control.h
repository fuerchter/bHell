#ifndef CONTROL
#define CONTROL

#include "SFML\Window.hpp"
#include "Thor\Events\InputNames.hpp"

#include "Setting.h"

class Control
{
public:
	//Writes Error into type
	Control();
	Control(Setting setting);

	int axisPosition();
	void setThreshold(int threshold);
	bool axisMoved();
	bool buttonPressed();
	bool menuButtonPressed(sf::Event currentEvent);
private:
	//type is no enum because it has to be read out from the config
	string type_;
	sf::Keyboard::Key key_;
	sf::Mouse::Button mouseButton_;
	int joystick_;
	int joystickButton_;
	sf::Joystick::Axis joystickAxis_;
	int joystickDirection_;
	int lastJoystickPosition_;
	int threshold_;
	int sensitivity_;
};

#endif