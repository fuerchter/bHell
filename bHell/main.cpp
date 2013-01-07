#include <iostream>
using namespace std;

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "GameMenu.h"
#include "GameStates.h"
using GameStates::GameState;

int main()
{
	//TODO:
	//[make config order irrelevant] and fix empty line bug
	//[changeInt reset if nothing entered]
	//implement mouse
	//[add axisPosition and sensitivity to Control] and changing complete axis sensitivity and Up/Down/Left/Right autocomplete
	//convert axis position from int to float
	//Second player
	//outsource window creation
	//take care of Start state
	//check Setting and Control(types)
	//make GameMenu and main more abstract
	//resolution independence!
	//Memory/CPU usage

	GameState state=GameStates::Video;
	GameMenu menu(state);
	SettingCategory controls=menu.getControls();
	SettingCategory video=menu.getVideo();

	int width=video.getSetting("Width").getAttInt();
	int height=video.getSetting("Height").getAttInt();
	bool vsync=video.getSetting("VSync").getAttBool();
	int framecap=video.getSetting("Framecap").getAttInt();
	bool windowed=video.getSetting("Windowed").getAttBool();
	bool showfps=video.getSetting("Show FPS").getAttBool();

	sf::RenderWindow window;
	if(windowed)
	{
		window.create(sf::VideoMode(width, height), "Game", sf::Style::Close);
	}
	else
	{
		window.create(sf::VideoMode(width, height), "Game", sf::Style::Fullscreen);
	}
	window.setFramerateLimit(framecap);
	window.setVerticalSyncEnabled(vsync);

	sf::Clock clock;

	while(window.isOpen())
	{
		sf::Time time=clock.getElapsedTime();
		clock.restart();
		if(showfps)
		{
			int fps;
			if(time.asMicroseconds()==0)
			{
				fps=0;
			}
			else
			{
				fps=1000000/time.asMicroseconds();
			}
			cout << fps << endl;
		}

		sf::Event currentEvent;
		while(window.pollEvent(currentEvent))
		{
			switch(currentEvent.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			/*case sf::Event::JoystickMoved:
				cout << "Joystick: " << currentEvent.joystickMove.joystickId << endl;
				cout << "Axis: " << thor::toString(currentEvent.joystickMove.axis) << endl;
				cout << "Position: " << currentEvent.joystickMove.position << endl;
				break;*/
			default:
				break;
			}

			if(state==GameStates::Quit)
			{
				window.close();
			}
			else if(state==GameStates::Start)
			{

			}
			else
			{
				state=menu.update(currentEvent);
				if(menu.videoChanged())
				{
					video=menu.getVideo();
					width=video.getSetting("Width").getAttInt();
					height=video.getSetting("Height").getAttInt();
					vsync=video.getSetting("VSync").getAttBool();
					framecap=video.getSetting("Framecap").getAttInt();
					windowed=video.getSetting("Windowed").getAttBool();
					showfps=video.getSetting("Show FPS").getAttBool();
					if(windowed)
					{
						window.create(sf::VideoMode(width, height), "Game", sf::Style::Close);
					}
					else
					{
						window.create(sf::VideoMode(width, height), "Game", sf::Style::Fullscreen);
					}
					window.setFramerateLimit(framecap);
					window.setVerticalSyncEnabled(vsync);
				}
				if(state==GameStates::Start)
				{
					//INITIALIZE MAIN AND REMOVE MENU
				}
			}
		}
		window.clear(sf::Color(255,0,0));

		if(state!=GameStates::Start && state!=GameStates::Quit)
		{
			vector<sf::Text> texts=menu.constructText();
			for(int i=0; i<texts.size(); i++)
			{
				window.draw(texts[i]);
			}
		}

		window.display();
	}
}