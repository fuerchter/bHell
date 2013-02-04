#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "Presets.h"
#include "MenuManager.h"
#include "WindowHelper.h"
#include "GameStates.h"
using GameStates::GameState;

int main()
{
	GameState state=GameStates::Menu;

	MenuManager *menu=new MenuManager(Presets::manager(state));
	SettingCategory controls=menu->getCategory(GameStates::Controls);
	SettingCategory video=menu->getCategory(GameStates::Video);

	sf::RenderWindow *window=new sf::RenderWindow;
	WindowHelper helper(video);
	helper.createWindow(window);

	sf::Clock clock;

	while(window->isOpen())
	{
		sf::Time time=clock.getElapsedTime();
		clock.restart();

		//FIND A WAY TO GET RID OF THIS
		helper.showFps(time);

		sf::Event currentEvent;
		while(window->pollEvent(currentEvent))
		{
			switch(currentEvent.type)
			{
			case sf::Event::Closed:
				window->close();
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
				window->close();
			}
			else if(state==GameStates::Start)
			{

			}
			else
			{
				state=menu->update(currentEvent);
				if(menu->categoryChanged(GameStates::Video))
				{
					video=menu->getCategory(GameStates::Video);
					helper.setVideo(video);
					helper.createWindow(window);
				}
				if(state==GameStates::Start)
				{
					//INITIALIZE MAIN AND REMOVE MENU
					delete menu;
					menu=NULL;
				}
			}
		}
		window->clear(sf::Color(255,0,0));

		if(state!=GameStates::Start && state!=GameStates::Quit)
		{
			vector<sf::Text> texts=menu->constructText();
			for(int i=0; i<texts.size(); i++)
			{
				//text origin independent from its scale factor?

				//resolution independence
				texts[i].setPosition(helper.relPosition(texts[i].getPosition()));

				//Just scaling
				//texts[i].setScale(helper.getFactor());
				
				//CharSize then scaling
				/*//Saving position to use after charSize was set
				sf::Vector2f pos=texts[i].getPosition();

				//calculating desired size from current and factors
				sf::Vector2f size=TextBounds::getLocalSize(texts[i]);
				sf::Vector2f desired(size.x*helper.getFactor().x, size.y*helper.getFactor().y);
				int charSize=TextBounds::getCharSize(texts[i], desired, 1, 30);
				texts[i].setCharacterSize(charSize);

				//calculating size correction
				size=TextBounds::getLocalSize(texts[i]);
				sf::Vector2f factor(desired.x/size.x, desired.y/size.y);
				texts[i].setScale(factor);

				//correcting position
				size=TextBounds::getLocalSize(texts[i]);
				texts[i].setOrigin(size.x/2, size.y/2);
				texts[i].setPosition(pos);*/

				window->draw(texts[i]);
			}
		}

		window->display();
	}
}