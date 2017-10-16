#ifndef MONSTER_H
#define MONSTER_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "imageManager.h"

enum class Races {
	ORC,
	TROLL,
	GOBLIN
};

enum class CombatState {
	MOVING_FORWARD,
	MOVING_BACKWARD,
	ATTACKING,
	IDLE
};

class Monster {
	double m_health;
	double m_attackPower;
	double m_defensePower;
	double m_speed;
	Races m_race;
	sf::Sprite m_sprite;
	CombatState combatState;
	sf::Vector2f destination;
	sf::Vector2f origin;
public:
	Monster(std::map<std::string, double>&, Races, texture_manager& textMan);
	~Monster();

	int getDamage(Monster&);
	void draw(sf::RenderWindow&);
	void printStat();
	void setPosition(sf::Vector2f&);
	void setDestination(sf::Vector2f&);
	sf::Vector2f getPosition();
	void move();
	CombatState getCombatState();
	void setCombatState(CombatState);
	double getSpeed();
	double getHealth();
	Races getRace();
	bool isAtDestination();
	sf::Vector2f getOrigin();
	void setOrigin(sf::Vector2f&);
};
#endif