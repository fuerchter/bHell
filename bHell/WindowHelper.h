#ifndef WINDOWHELPER
#define WINDOWHELPER

#include <iostream>
#include <queue>
using namespace std;

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "SettingCategory.h"

class WindowHelper
{
public:
	//Initializes video_ with the Preset Category and calls setVideo
	WindowHelper(SettingCategory video);

	//Fills up video_ with new values if the Setting title matches
	void setVideo(SettingCategory video);
	void createWindow(sf::RenderWindow *window);

	int calculateFps(sf::Time time);
	//NEEDS TO BE DRAWN
	void showFps(sf::Time time);
private:
	SettingCategory video_;
};

#endif