#include "ControlManager.h"
#include "SettingCategory.h"

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include <iostream>
using namespace std;

void bla()
{
	/*Setting test("Up", "Joystick_1_Y_-1", SettingTypes::Input);
	Control bla(test);*/
	SettingCategory rup("Controls");
	ControlManager bla(rup);
	

	sf::RenderWindow window(sf::VideoMode(20, 20), "Game", sf::Style::Close);

	while(window.isOpen())
	{
		sf::Event currentEvent;
		while(window.pollEvent(currentEvent))
		{
			switch(currentEvent.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;

				
			}
			//cout << bla.getControl("Up").axisMoved() << endl;
			cout << bla.getControl("Up").lastJoystickPosition_ << endl;
			/*cout << bla.axisMoved() << endl;
			cout << bla.lastJoystickPosition_ << endl;*/
		}
		window.display();
	}
}