#ifndef MENUELEMENT
#define MENUELEMENT

#include "GameStates.h"
using GameStates::GameState;
#include "Setting.h"

class MenuElement
{
public:
	MenuElement(string title, GameState action);
	MenuElement(string title, GameState action, Setting *setting);
	~MenuElement();

	string getTitle();
	GameState getAction();
	//Returns null pointer if no setting available
	Setting *getSetting();
	bool hasSetting();
private:
	string title_;
	GameState action_;
	Setting *setting_;
};

#endif