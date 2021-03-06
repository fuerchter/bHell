#include "Config.h"

bool Config::doesCategoryExist(SettingCategory category)
{
	string temp="";
	fstream file("config.cfg");
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, temp);
			if(temp=="["+ category.getTitle()+ "]")
			{
				file.close();
				return true;
			}
		}
	}
	file.close();
	return false;
}

SettingCategory Config::readCategory(SettingCategory category)
{
	vector<Setting> settings;
	string temp="";
	fstream file("config.cfg");
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, temp);
			if(temp=="["+ category.getTitle()+ "]")
			{
				//saves the config entries in a map
				map<string, string> cSettings;
				for(int i=0; file.good(); i++)
				{
					getline(file, temp);
					if(temp.empty() || temp[0]=='[')
					{
						break;
					}
					size_t pos=temp.find("=");
					string attribute=temp.substr(pos+1);

					//now has Setting title
					temp.resize(pos);
					cSettings.insert(pair<string, string>(temp, attribute));
				}

				//goes through each entry in the given category and checks whether there was a config entry with the same title
				for(int i=0; i<category.getSeSize(); i++)
				{
					string attribute=category.getSetting(i).getAttribute();

					//checks whether entry in category is in cSettings
					if(cSettings.find(category.getSetting(i).getTitle())!=cSettings.end())
					{
						attribute=cSettings[category.getSetting(i).getTitle()];
					}
					settings.push_back(Setting(category.getSetting(i).getTitle(), attribute, category.getSetting(i).getType()));
				}
				break;
			}
		}
		file.close();
	}
	else
	{
		//Error message in case file wasn't able to be opened
	}

	return SettingCategory(category.getTitle(), settings);
}

SettingCategory Config::getCategory(SettingCategory category)
{
	if(doesCategoryExist(category) || category.getSeSize()==0)
	{
		return readCategory(category);
	}
	else
	{
		writeCategory(category);
		return category;
	}
}

void Config::removeCategory(SettingCategory category)
{
	if(doesCategoryExist(category))
	{
		string temp="";
		ofstream newFile("newconfig.cfg");
		fstream file("config.cfg");

		if(file.is_open())
		{
			while(file.good())
			{
				getline(file, temp);
				//reads the next lines without using them to skip past the category to be removed
				if(temp=="["+ category.getTitle()+ "]")
				{
					while(file.good())
					{
						getline(file, temp);
						//the category was skipped over so the function goes back to writing lines
						if(temp.empty() || temp[0]=='[')
						{
							break;
						}
					} 
				}
				else
				{
					//if this line is the last of a category (a newline generally) nothing is written (fixed newline bug)
					if(file.peek()==file.eof() || file.peek()=='[')
					{

					}
					else
					{
						newFile << temp+ "\n";
					}
				}
			}
			file.close();
			remove("config.cfg");
			newFile.close();
			rename("newconfig.cfg", "config.cfg");
		}
		else
		{
			//Error message in case file wasn't able to be opened
		}
	}
}

void Config::writeCategory(SettingCategory category)
{
	removeCategory(category);

	ofstream file("config.cfg", ios_base::app);
	if(file.is_open())
	{
		file << "[" +category.getTitle()+ "]\n";
		for(int i=0; i<category.getSeSize(); i++)
		{
			file << category.getSetting(i).getTitle()+ "=" +category.getSetting(i).getAttribute()+ "\n";
			if(i==category.getSeSize()-1)
			{
				file << "\n";
			}
		}
		file.close();
	}
}