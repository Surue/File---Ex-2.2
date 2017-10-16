#include "monster.h"

Monster::Monster(std::map<std::string, double>& data, Races race, texture_manager& textMan) : m_race(race) {
	m_health = data.find("HP")->second;
	m_attackPower = data.find("AP")->second;
	m_defensePower = data.find("DP")->second;
	m_speed = data.find("SP")->second;
	combatState = CombatState::IDLE;
	std::string imagePath;
	switch (m_race) {
		case Races::ORC:
			imagePath = "../data/Orc_Texture.png";
			break;

		case Races::TROLL:
			imagePath = "../data/Troll_Texture.png";
			break;

		case Races::GOBLIN:
			imagePath = "../data/Goblin_Texture.png";
			break;

		default:
			std::cout << "ERROR : This races does not exist\n";
			break;
	}


	m_sprite.setTexture(textMan.getTexture(imagePath));
}

Monster::~Monster() {
}

int Monster::getDamage(Monster & m) {
	double damage = m_attackPower - m.m_defensePower;
	if (damage <= 0) {
		damage = 1;
	}
	m.m_health -= damage;

	return damage;
}

void Monster::draw(sf::RenderWindow & window) {
	window.draw(m_sprite);
}

void Monster::printStat() {
	std::cout << "Le monstre de race " << (int)m_race << "\n"
		<< "HP = " << m_health << "\n"
		<< "AP = " << m_attackPower << "\n"
		<< "DP = " << m_defensePower << "\n"
		<< "SP = " << m_speed << "\n";
}

void Monster::setPosition(sf::Vector2f & vect) {
	m_sprite.setPosition(vect);
}

void Monster::setDestination(sf::Vector2f & dest) {
	destination = dest;
}

sf::Vector2f Monster::getPosition() {
	return m_sprite.getPosition();
}

void Monster::move() {
	sf::Vector2f vect;
	if (sf::Vector2f(destination - m_sprite.getPosition()).x < 0) {
		vect = sf::Vector2f(-7, 0);
	}else {
		vect = sf::Vector2f(7, 0);
	}
	m_sprite.move(vect);
}

CombatState Monster::getCombatState() {
	return combatState;
}

void Monster::setCombatState(CombatState state) {
	combatState = state;
}

double Monster::getSpeed() {
	return m_speed;
}

double Monster::getHealth() {
	return m_health;
}

Races Monster::getRace() {
	return m_race;
}

bool Monster::isAtDestination() {
	if (destination.x - 5 <= m_sprite.getPosition().x && destination.x + 5 >= m_sprite.getPosition().x) {
		setPosition(destination);
	}
	return  destination == m_sprite.getPosition();
}

sf::Vector2f Monster::getOrigin() {
	return origin;
}

void Monster::setOrigin(sf::Vector2f & ori) {
	origin = ori;
	setPosition(origin);
}
