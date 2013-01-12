#ifndef MENU
#define MENU

#include "SFML\Graphics.hpp"

#include "MenuElement.h"
#include "SettingCategory.h"

class Menu
{
public:
	//Creates a preset menu from a GameState, members may be uninitialized if state didn't match a preset
	Menu(GameState state);
	//Converts SettingCategory to MenuElement vector to create a menu
	Menu(GameState state, GameState escAction, SettingCategory category);
	//Most abstract constructor
	Menu(string title, GameState escAction, vector<MenuElement> elements);

	void goUp();
	void goDown();
	GameState enter();
	GameState escape();
	int getCurrNo();
	string getTitle();

	MenuElement getEl(int i);
	MenuElement getCurrEl();
	bool hasCurrSetting();
	//Returns NULL if the current element doesn't have a setting
	Setting *getCurrSetting();
	//Creates a vector that contains all element titles
	vector<string> getElTitles();
	//Creates MenuTexts from the current MenuElements with a default vSpacing and preset normal and hover state colors
	vector<sf::Text> constructText(sf::Font &font, int vSpacing=30, sf::Color normal=sf::Color(255, 255, 255), sf::Color hover=sf::Color(0, 0, 0));

	//Returns null if current element does not contain a setting
	string getCurrAtt();
	void setCurrAtt(string attribute);
	Setting::Type getCurrType();

	SettingCategory constructCat();
private:
	string title_;
	GameState escAction_;
	vector<MenuElement> elements_;
	int currNo_;
};

#endif