#include "Presets.h"

SettingCategory Presets::category(string title)
{
	vector<Setting> settings;

	//PRESETS
	if(title=="Video")
	{
		sf::VideoMode desktop=sf::VideoMode::getDesktopMode();
		stringstream width;
		width << desktop.width;
		stringstream height;
		height << desktop.height;
		settings.push_back(Setting("Width", width.str(), Setting::Int));
		settings.push_back(Setting("Height", height.str(), Setting::Int));
		settings.push_back(Setting("VSync", "0", Setting::Bool));
		settings.push_back(Setting("Framecap", "60", Setting::Int));
		settings.push_back(Setting("Windowed", "0", Setting::Bool));
		settings.push_back(Setting("Show FPS", "0", Setting::Bool));
	}
	else if(title.find("Controls")==0)
	{
		settings.push_back(Setting("Up", "Keyboard_Up", Setting::Input));
		settings.push_back(Setting("Down", "Keyboard_Down", Setting::Input));
		settings.push_back(Setting("Left", "Keyboard_Left", Setting::Input));
		settings.push_back(Setting("Right", "Keyboard_Right", Setting::Input));
		settings.push_back(Setting("Enter", "Keyboard_Return", Setting::Input));
		settings.push_back(Setting("Back", "Keyboard_Escape", Setting::Input));
	}
	else if(title=="Menu Controls")
	{
		settings.push_back(Setting("Up", "Keyboard_Up", Setting::Input));
		settings.push_back(Setting("Down", "Keyboard_Down", Setting::Input));
		settings.push_back(Setting("Left", "Keyboard_Left", Setting::Input));
		settings.push_back(Setting("Right", "Keyboard_Right", Setting::Input));
		settings.push_back(Setting("Enter", "Keyboard_Return", Setting::Input));
		settings.push_back(Setting("Back", "Keyboard_Escape", Setting::Input));
	}

	return SettingCategory(title, settings);
}

Menu Presets::menu(GameState state)
{
	vector<MenuElement> elements;
	string title="";
	GameState escAction=GameStates::Quit;

	//PRESETS
	if(state==GameStates::Menu)
	{
		title="Menu";
		elements.push_back(MenuElement("Start", GameStates::Start));
		elements.push_back(MenuElement("Options", GameStates::Options));
		elements.push_back(MenuElement("Quit", GameStates::Quit));
		escAction=GameStates::Quit;
	}
	else if(state==GameStates::Options)
	{
		title="Options";
		elements.push_back(MenuElement("Video", GameStates::Video));
		elements.push_back(MenuElement("Controls", GameStates::Controls));
		escAction=GameStates::Menu;
	}

	return Menu(title, escAction, elements);
}

MenuManager Presets::manager(GameState state)
{
	map<GameState, Menu> menus;

	//PRESETS
	SettingCategory video(Presets::category("Video"));
	video=Config::getCategory(video);
	SettingCategory controls(Presets::category("Controls"));
	controls=Config::getCategory(controls);
	menus.insert(pair<GameState, Menu>(GameStates::Menu, Presets::menu(GameStates::Menu)));
	menus.insert(pair<GameState, Menu>(GameStates::Options, Presets::menu(GameStates::Options)));
	menus.insert(pair<GameState, Menu>(GameStates::Video, Menu(GameStates::Video, GameStates::Options, video)));
	menus.insert(pair<GameState, Menu>(GameStates::Controls, Menu(GameStates::Controls, GameStates::Options, controls)));

	return MenuManager(state, menus);
}