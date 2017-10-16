#include <iostream>
#include "monsterManager.h"
#include <SFML\Graphics.hpp>
#include "json.hpp"
#include <fstream>
#include <map>
#include <list>

using json = nlohmann::json;

Races convert(const std::string& str) {
	if (str == "ORC") {
		return Races::ORC;
	} else if(str == "TROLL"){
		return Races::TROLL;
	} else if (str == "GOBLIN") {
		return Races::GOBLIN;
	}

	std::cout << "ERROR : In file json, races doesn't exist\n";
}

int main() {

	//INITIALISE MOSNTERS
	//Open json file
	std::ifstream file;
	file.exceptions(std::ios::failbit);
	try {
		file.open("../data/Data_Monster.json", std::ios::in);
	}
	catch (std::ios_base::failure &fail) {
		std::cout << "ERROR: File not found\n";
		system("pause");
		return EXIT_FAILURE;
	}
	file.exceptions(std::ios::goodbit);

	json j;
	j << file;

	//SFML - INITIALISE WINDOW
	sf::RenderWindow window(sf::VideoMode(500, 250), "Exercie 2.2");
	window.setFramerateLimit(60.f);

	//TEXTURE MANAGER
	texture_manager img_mgr;
	img_mgr.addResourceDirectory("../data");

	//Read all monsters
	MonsterManager monsterManager(window);
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::map<std::string, double> tempMonsterData;
		Races tempRace;
		//Read data of one monster
		for (json::iterator monster = it.value().begin(); monster != it.value().end(); ++monster) {
			if (monster.key() == "RACES") {
				tempRace = convert(monster.value());
				continue;
			}
			tempMonsterData.insert(std::pair<std::string, double>(monster.key(), monster.value()));
		}
		
		//Create Monster in the manager
		monsterManager.addMonster(tempMonsterData, tempRace, img_mgr);
	}


	//SFML - GAME LOOP
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
				break;
			}
		}

		//Battle
		window.clear();
		if (monsterManager.mustBattle()) {
			monsterManager.manageBattle();
		} else {
			std::cout << "Plus de combat\n";
		}
		monsterManager.draw(window);
		window.display();
	}

	system("pause");
	return EXIT_SUCCESS;
}