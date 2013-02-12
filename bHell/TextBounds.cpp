#include "TextBounds.h"

sf::Vector2f TextBounds::getLocalSize(const sf::Text& text)
{
    const sf::String str = text.getString() + '\n';

    float maxLineWidth = 0.f;
    float lineWidth = 0.f;
    unsigned int lines = 0;

	//Goes through each character of the text
    for (sf::String::ConstIterator itr = str.begin(); itr != str.end(); ++itr)
    {
		//In case a new line was reached add to lines counter
        if (*itr == '\n')
        {
            ++lines;

			//Get whether the current line was the longest or the current maximum
            maxLineWidth = std::max(maxLineWidth, lineWidth);

			//Reset lineWidth
            lineWidth = 0.f;
        }
        else
        {
			//Add current character size to lineWidth
            lineWidth += text.getFont()->getGlyph(*itr, text.getCharacterSize(), text.getStyle() & sf::Text::Bold).advance;
        }
    }

	//Calculate lineHeight
    const float lineHeight = static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()));
    return sf::Vector2f(maxLineWidth, lines * lineHeight);
}

int TextBounds::getCharSize(sf::Text text, sf::Vector2f size, int threshold, int midCharSize)
{
	int charSize=midCharSize;

	sf::Vector2f newsize=getLocalSize(text);

	while((abs(newsize.x-size.x)>threshold && abs(newsize.y-size.y)>threshold) && midCharSize!=1)
	{
		midCharSize/=2;
		if(newsize.x-size.x>threshold && newsize.y-size.y>threshold)
		{
			charSize-=midCharSize;
		}
		else if(newsize.x-size.x<(threshold*(-1)) && newsize.y-size.y<(threshold*(-1)))
		{
			charSize+=midCharSize;
		}

		text.setCharacterSize(charSize);
		newsize=getLocalSize(text);
	}
	return charSize;
}