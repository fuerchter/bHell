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
	calculateScreenSpace();
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


void WindowHelper::calculateScreenSpace()
{
	if(video_.getSetting("Border").getAttBool())
	{
		float desAspect=(float)defWidth/(float)defHeight;
		float aspect=(float)video_.getSetting("Width").getAttInt()/(float)video_.getSetting("Height").getAttInt();
		sf::Vector2f newSize(video_.getSetting("Width").getAttInt(), video_.getSetting("Height").getAttInt());
		if(aspect>desAspect)
		{
			newSize.x=newSize.y*desAspect;
		}
		else if(aspect<desAspect)
		{
			newSize.y=newSize.x/desAspect;
		}
		sf::Vector2f newPosition(video_.getSetting("Width").getAttInt()/2-newSize.x/2, video_.getSetting("Height").getAttInt()/2-newSize.y/2);

		screenSpace_=sf::RectangleShape(newSize);
		screenSpace_.setPosition(newPosition);
	}
	else
	{
		screenSpace_=sf::RectangleShape(sf::Vector2f(video_.getSetting("Width").getAttInt(), video_.getSetting("Height").getAttInt()));
	}
}

bool WindowHelper::getBorder()
{
	return video_.getSetting("Border").getAttBool();
}

sf::RectangleShape WindowHelper::getScreenSpace()
{
	return screenSpace_;
}

sf::Vector2f WindowHelper::getFactor()
{
	float width=screenSpace_.getSize().x;
	float height=screenSpace_.getSize().y;
	return sf::Vector2f(width/(float)defWidth, height/(float)defHeight);
}

sf::Vector2f WindowHelper::relPosition(sf::Vector2f position)
{
	sf::Vector2f res(position.x*getFactor().x, position.y*getFactor().y);
	if(video_.getSetting("Border").getAttBool())
	{
		res.x+=screenSpace_.getPosition().x;
		res.y+=screenSpace_.getPosition().y;
	}
	return res;
}