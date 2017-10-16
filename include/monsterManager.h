#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "monster.h";
#include <list>
#include <map>
#include <iostream>
#include <SFML\Graphics.hpp>

enum BattleState {
	NO_FIGHT,
	M_1_FIGHT,
	M_2_FIGHT,
	END_FIGHT,
	NO_MORE_FIGHT
};

class MonsterManager {
private:
	std::list<Monster> m_monstersList;
	BattleState m_battleState;
	sf::RenderWindow& m_window;
	std::list<sf::Text> listText;
	sf::Font font;
public:
	MonsterManager(sf::RenderWindow&);
	~MonsterManager();

	void addMonster(std::map<std::string, double>, Races, texture_manager&);
	bool removeDead();
	void printMonsters();
	void manageBattle();
	void battle(Monster&, Monster&);
	void attack(Monster&, Monster&);
	bool mustBattle();
	bool onlyOneRace();
	void addText(std::string, sf::Vector2f);
	void draw(sf::RenderWindow&);
};

#endif