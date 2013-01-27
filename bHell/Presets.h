#ifndef PRESETS
#define PRESETS

#include "MenuManager.h"

class Presets
{
public:
	static SettingCategory category(string title);
	static Menu menu(GameState state);
	static MenuManager manager(GameState state);
};

#endif