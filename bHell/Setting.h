#ifndef SETTING
#define SETTING

#include <string>
#include <sstream>
using namespace std;

class Setting
{
public:
	enum Type
	{
		Error, Int, Bool, Input
	};
	Setting(string title, string attribute, Type type);
	string getTitle();
	string getAttribute();
	//Returns -1 if Setting was not of type int and 0 if it was type int but attribute was not
	int getAttInt();
	bool getAttBool();
	void setAttribute(string attribute);
	void toggleBool();
	Setting::Type getType();
	
private:
	string title_;
	string attribute_;
	Type type_;
};

#endif