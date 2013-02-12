#ifndef CONTROL
#define CONTROL

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
	void setThreshold(int threshold);
	//gets current position dependent from this Control's sensitivity
	float axisPosition();
	bool axisMoved();
	bool buttonPressed();
	bool menuButtonPressed(sf::Event currentEvent);
private:
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