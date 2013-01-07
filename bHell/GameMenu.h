#ifndef GAMEMENU
#define GAMEMENU

#include "Menu.h"
#include "Config.h"
#include "ControlManager.h"

class GameMenu
{
public:
	GameMenu(GameState state);
	GameState update(sf::Event currentEvent);
	//Creates MenuTexts, font has to be changed internally
	vector<sf::Text> constructText(int vSpacing=30, sf::Color normal=sf::Color(255, 255, 255), sf::Color hover=sf::Color(0, 0, 0));
	SettingCategory getVideo();
	SettingCategory getControls();
	bool videoChanged();
private:
	GameState state_;
	Menu menu_;
	sf::Font font_;
	vector<sf::Text> texts_;
	SettingCategory video_;
	SettingCategory controls_;
	Config config_;
	ControlManager input_;
	bool changeInt_;
	string currAttribute_;
	bool changeInput_;
	bool videoChanged_;
	void controlsChanged();
};

#endif