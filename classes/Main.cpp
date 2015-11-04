#include <SFML/Graphics.hpp>
#include "Game.h"
#include <fstream>
#include <sstream>
#include "JSON/JSON.h"

// This is a comment

void loadJSONData(std::string const & filename, std::string & jsonData);
void parseJSONData(std::string const & jsonData);
std::string wStringToString(std::wstring const & wstr);

int main() {
	std::string jsonData;
	std::string filename = ".\\data\\GameData.json";
	loadJSONData(filename, jsonData);

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	Game *the_Game = new Game();

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		the_Game->Run(window);
		window.display();
	}

}

void loadJSONData(std::string const & filename, std::string & jsonData)
{
	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			jsonData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		throw std::exception(errorMessage.c_str());
	}
}

std::string wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}

void parseJSONData(std::string const & jsonData)
{
	// Retrieve the main (root) object
	JSONValue * value = JSON::Parse(jsonData.c_str());
	JSONObject root = value->AsObject();
	
	//Search through each element of the list.
	JSONObject level1 = root[L"level_1"]->AsObject();
	JSONObject level1_wave1 = level1[L"wave_1"]->AsObject();
	//Get the time at which the first wave should appear.
	int level1_wave1_spawntime = level1_wave1[L"spawn_time"]->AsNumber();
	//Get enemy position information.
	JSONArray level1_wave1_enemies = level1_wave1[L"enemy"]->AsArray();
	//FIND A WAY TO GET THIS INFORMATION AND USE IT TO SPAWN ENEMIES.

	JSONObject level1_wave2 = level1[L"wave_2"]->AsObject();
	int level1_wave2_spawntime = level1_wave2[L"spawn_time"]->AsNumber();
	JSONArray level1_wave2_enemies = level1_wave2[L"enemy"]->AsArray();
	//FIND A WAY TO GET THIS INFORMATION AND USE IT TO SPAWN ENEMIES.

	/*The following is the code that existed in the original program given by Ross. Use this as a guideline.
	// Load the global settings object.
	JSONObject globalSettings = root[L"global_settings"]->AsObject();
	// Load the texture image filename
	std::string image_file = wStringToString(globalSettings[L"texture_image_file"]->AsString());
	// Load the tower rotation origin
	JSONObject towerRotation = globalSettings[L"tower_rotation_origin"]->AsObject();
	int x = towerRotation[L"x"]->AsNumber();
	int y = towerRotation[L"y"]->AsNumber();
	// Load the tower positions
	JSONArray towerPositions = globalSettings[L"tower_positions"]->AsArray();
	int size = towerPositions.size();*/
}