#ifndef MENUMANAGER
#define MENUMANAGER

#include "Menu.h"
#include "Config.h"
#include "ControlManager.h"

class MenuManager
{
public:
	MenuManager(GameState state);
	MenuManager(GameState state, map<GameState, Menu> menus);
	GameState update(sf::Event currentEvent);
	//Creates MenuTexts, font has to be changed internally
	vector<sf::Text> constructText(int vSpacing=30, sf::Color normal=sf::Color(255, 255, 255), sf::Color hover=sf::Color(0, 0, 0));
	SettingCategory getCategory(GameState state);
	bool categoryChanged(GameState state);
private:
	GameState state_;
	Menu menu_;
	//Contains all the Menus that can be displayed
	map<GameState, Menu> menus_;
	//If a Setting(Category) in a certain GameState was changed the GameState is present here (access via categoryChanged)
	vector<GameState> changed_;
	//The current Setting type to be changed (is set to error if no Setting is being changed)
	Setting::Type change_;
	string currAttribute_;
	//Adds the current GameState to changed_ and writes to Config
	void changeSetting(Setting::Type type);

	sf::Font font_;
	vector<sf::Text> texts_;
	//CONTROLMANAGER MAY NEED TO BE ASSIGNED TO MENUCONTROLS
	ControlManager input_;
};

#endif