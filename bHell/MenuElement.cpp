#include "MenuElement.h"

MenuElement::MenuElement(string title, GameState action):
title_(title), action_(action)
{
	setting_=NULL;
}

MenuElement::MenuElement(string title, GameState action, Setting *setting):
title_(title), action_(action), setting_(setting)
{

}

MenuElement::~MenuElement()
{
	delete setting_;
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
	return setting_;
}

bool MenuElement::hasSetting()
{
	if(setting_!=NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}