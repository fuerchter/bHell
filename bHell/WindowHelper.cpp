#include "WindowHelper.h"

WindowHelper::WindowHelper(SettingCategory video):
video_(Presets::category("Video"))
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
	sf::VideoMode temp=sf::VideoMode::getDesktopMode();
	bool windowed=video_.getSetting("Windowed").getAttBool();
	int width=video_.getSetting("Width").getAttInt();
	int height=video_.getSetting("Height").getAttInt();

	//fixes #22 (Large resolution makes window disappear)
	if(windowed)
	{
		if(width>temp.width)
		{
			width=temp.width;
		}
		if(height>temp.height)
		{
			height=temp.height;
		}
	}

	if(windowed)
	{
		window->create(sf::VideoMode(width, height), "Game", sf::Style::Close);
	}
	else
	{
		window->create(sf::VideoMode(width, height), "Game", sf::Style::Fullscreen);
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
			return 1000000/(int)time.asMicroseconds();
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


sf::Vector2f WindowHelper::getFactor()
{
	float width=(float)video_.getSetting("Width").getAttInt();
	float height=(float)video_.getSetting("Height").getAttInt();
	return sf::Vector2f(width/(float)defWidth, height/(float)defHeight);
}

sf::Vector2f WindowHelper::relPosition(sf::Vector2f position)
{
	return sf::Vector2f(position.x*getFactor().x, position.y*getFactor().y);
}