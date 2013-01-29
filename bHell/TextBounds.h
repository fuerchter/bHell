#ifndef TEXTBOUNDS
#define TEXTBOUNDS

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class TextBounds
{
public:
	static sf::Vector2f getLocalSize(const sf::Text& text);
};

#endif