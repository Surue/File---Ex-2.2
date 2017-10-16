#include "..\include\monsterManager.h"
#define CHARACTER_SIZE 24

MonsterManager::MonsterManager(sf::RenderWindow& window): m_window(window) {
	m_battleState = BattleState::NO_FIGHT;

	if (!font.loadFromFile("../data/Powerful.ttf")) {
		std::cout << "ERROR: unable to load font\n";
	}
}

MonsterManager::~MonsterManager() {
}

void MonsterManager::addMonster(std::map<std::string, double> data, Races race, texture_manager& textMan) {
	m_monstersList.push_back(Monster(data, race, textMan));
}

bool MonsterManager::removeDead() {
	bool hasRemoved = false;
	for (auto i = m_monstersList.begin(); i != m_monstersList.end();) {
		if (i->getHealth() <= 0) {
			i = m_monstersList.erase(i);
			hasRemoved = true;
		} else {
			++i;
		}
	}
	return hasRemoved;
}

void MonsterManager::printMonsters() {
	for (auto monster : m_monstersList) {
		monster.printStat();
	}
}

void MonsterManager::manageBattle() {
	if (onlyOneRace()) {
		m_battleState = BattleState::NO_MORE_FIGHT;
	} else {
		for (auto i = m_monstersList.begin(); i != --m_monstersList.end(); i++) {
			auto next = std::next(i, 1);
			if (i->getRace() != next->getRace()) {
				battle(*i, *next);
				return;
			}
		}
	}
}

void MonsterManager::battle(Monster & m1, Monster & m2) {
	
	switch (m_battleState) {
	case BattleState::M_1_FIGHT:
		attack(m1, m2);
		break;

	case BattleState::M_2_FIGHT:
		attack(m2, m1);
		break;

	case BattleState::END_FIGHT:
		break;

	case BattleState::NO_FIGHT:
		//Set at the right position both 
		m1.setOrigin(sf::Vector2f(50, m_window.getSize().y / 2 - 50));
		m2.setOrigin(sf::Vector2f(400, m_window.getSize().y / 2 - 50));
		if (m1.getSpeed() > m2.getSpeed()) {
			m_battleState = BattleState::M_1_FIGHT;
		} else {
			m_battleState = BattleState::M_2_FIGHT;
		}
		break;
	}

	if (removeDead()) {
		if (m_monstersList.size() == 1 || onlyOneRace()) {
		 	m_battleState = BattleState::NO_MORE_FIGHT;
		} 
	}
}

void MonsterManager::attack(Monster & attacker, Monster & attacked) {
	switch (attacker.getCombatState()) {
	case CombatState::IDLE:
		int offset;
		if (attacker.getPosition().x > attacked.getPosition().x) {
			offset = -50;
		} else {
			offset = 50;
		}
		attacker.setDestination(attacked.getPosition() - sf::Vector2f(offset, 0));
		attacker.setCombatState(CombatState::MOVING_FORWARD);
		break;

	case CombatState::MOVING_FORWARD:
		attacker.move();
		if (attacker.isAtDestination()) {
			attacker.setCombatState(CombatState::ATTACKING);
		}
		break;

	case CombatState::MOVING_BACKWARD:
		attacker.move();
		if (attacker.isAtDestination()) {
			attacker.setCombatState(CombatState::IDLE);
			if (m_battleState == BattleState::M_1_FIGHT) {
				m_battleState = BattleState::M_2_FIGHT;
			} else {
				m_battleState = BattleState::M_1_FIGHT;
			}
		}
		break;

	case CombatState::ATTACKING:
		int damage = attacker.getDamage(attacked);
		addText(std::to_string(damage), attacked.getPosition() - sf::Vector2f(0, 50));
		attacker.setCombatState(CombatState::MOVING_BACKWARD);
		attacker.setDestination(attacker.getOrigin());
		break;
	}
}

bool MonsterManager::mustBattle() {
	return m_battleState != BattleState::NO_MORE_FIGHT;
}

bool MonsterManager::onlyOneRace() {
	bool allSameRace = true;
	auto it = m_monstersList.begin();
	Races race = it->getRace();
	it++;
	for (it; it != m_monstersList.end(); it++) {
		if (it->getRace() != race) {
			allSameRace = false;
			it = --m_monstersList.end();
		}
	}

	return allSameRace;
}

void MonsterManager::addText(std::string str, sf::Vector2f pos) {
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(CHARACTER_SIZE);
	text.setFillColor(sf::Color::Red);
	text.setPosition(pos);
	text.setString(str);

	listText.push_back(text);
}

void MonsterManager::draw(sf::RenderWindow& window) {
	for (auto i : listText) {
		window.draw(i);
	}
	listText.clear();

	for (auto i = m_monstersList.begin(); i != --m_monstersList.end(); i++) {
		auto next = std::next(i, 1);
		if (i->getRace() != next->getRace()) {
			i->draw(window);
			next->draw(window);
			return;
		}
	}
}
