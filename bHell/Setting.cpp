#include "Setting.h"

Setting::Setting(string title, string attribute, SettingType type):
title_(title), attribute_(attribute), type_(type)
{

}

string Setting::getTitle()
{
	return title_;
}

string Setting::getAttribute()
{
	return attribute_;
}

int Setting::getAttInt()
{
	int res=0;
	if(type_==SettingTypes::Int)
	{
		stringstream convert(getAttribute());
		if(!(convert >> res))
		{

		}
	}
	else
	{
		res=-1;
	}
	return res;
}

bool Setting::getAttBool()
{
	int res=0;
	if(type_==SettingTypes::Bool)
	{
		stringstream convert(getAttribute());
		if(!(convert >> res))
		{
			res=0;
		}
	}
	else
	{
		res=0;
	}
	return res;
}

void Setting::setAttribute(string attribute)
{
	attribute_=attribute;
}

void Setting::toggleBool()
{
	if(type_==SettingTypes::Bool)
	{
		if(attribute_=="0")
		{
			attribute_="1";
		}
		else
		{
			attribute_="0";
		}
	}
	else
	{

	}
}

SettingType Setting::getType()
{
	return type_;
}