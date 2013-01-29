#ifndef WINDOWHELPER
#define WINDOWHELPER

#include <iostream>
#include <queue>
using namespace std;

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "Presets.h"

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

	sf::Vector2f getFactor();
	sf::Vector2f relPosition(sf::Vector2f position);
private:
	SettingCategory video_;
	static const int defWidth=1920;
	static const int defHeight=1080;
};

#endif