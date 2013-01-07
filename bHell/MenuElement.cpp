#include "MenuElement.h"

MenuElement::MenuElement(string title, GameState action):
title_(title), action_(action)
{
	setting_=NULL;
	hasSetting_=false;
}

MenuElement::MenuElement(string title, GameState action, Setting *setting):
title_(title), action_(action), setting_(setting)
{
	hasSetting_=true;
}


string MenuElement::getTitle()
{
	return title_;
}

GameState MenuElement::getAction()
{
	return action_;
}

Setting *MenuElement::getSetting()
{
	if(hasSetting_)
	{
		return setting_;
	}
	else
	{
		return NULL;
	}
}

bool MenuElement::hasSetting()
{
	return hasSetting_;
}