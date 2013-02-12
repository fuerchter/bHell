#ifndef TEXTBOUNDS
#define TEXTBOUNDS

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class TextBounds
{
public:
	static sf::Vector2f getLocalSize(const sf::Text& text);
	static int getCharSize(sf::Text text, sf::Vector2f size, int threshold, int midCharSize);
};

#endif