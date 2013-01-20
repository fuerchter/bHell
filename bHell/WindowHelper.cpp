#include "WindowHelper.h"

WindowHelper::WindowHelper(SettingCategory video):
video_("Video")
{
	setVideo(video);
}


void WindowHelper::setVideo(SettingCategory video)
{
	for(int i=0; i<video_.getSeSize(); i++)
	{
		//if a Setting in the current Category was found it will be filled up
		if(video.getSetting(video_.getSetting(i).getTitle()).getType()!=Setting::Error)
		{
			video_.setSetting(i, video.getSetting(i));
		}
	}
}

void WindowHelper::createWindow(sf::RenderWindow *window)
{
	if(video_.getSetting("Windowed").getAttBool())
	{
		window->create(sf::VideoMode(video_.getSetting("Width").getAttInt(), video_.getSetting("Height").getAttInt()), "Game", sf::Style::Close);
	}
	else
	{
		window->create(sf::VideoMode(video_.getSetting("Width").getAttInt(), video_.getSetting("Height").getAttInt()), "Game", sf::Style::Fullscreen);
	}
	window->setFramerateLimit(video_.getSetting("Framecap").getAttInt());
	window->setVerticalSyncEnabled(video_.getSetting("VSync").getAttBool());
}


int WindowHelper::calculateFps(sf::Time time)
{
	if(video_.getSetting("Show FPS").getAttBool())
	{
		if(time.asMicroseconds()==0)
		{
			return 0;
		}
		else
		{
			//factor to convert microsecond to second is 1000000
			return 1000000/time.asMicroseconds();
		}
	}
	else
	{
		return -1;
	}
}

void WindowHelper::showFps(sf::Time time)
{
	if(video_.getSetting("Show FPS").getAttBool())
	{
		cout << calculateFps(time) << endl;
	}
}