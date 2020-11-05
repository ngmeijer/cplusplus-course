#pragma once
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"
#include "../Headers/Character.hpp"

class Enemy : public Character
{
private:
	struct STRENGTH_VALUES {
		int strength3 = 3;
		int strength4 = 4;
		int strength5 = 5;
		int strength6 = 6;
		int strength7 = 7;
		int strength8 = 8;
		int strength9 = 9;
		int strength10 = 10;
	};

	struct HEAL_VALUES {
		int heal3 = 3;
		int heal4 = 4;
		int heal5 = 5;
		int heal6 = 6;
		int heal7 = 7;
		int heal8 = 8;
		int heal9 = 9;
		int heal10 = 10;
	};

	struct HEADSHOT_VALUES {
		int headshot3 = 3;
		int headshot4 = 4;
		int headshot5 = 5;
		int headshot6 = 6;
		int headshot7 = 7;
		int headshot8 = 8;
		int headshot9 = 9;
		int headshot10 = 10;
	};

public:
	int m_strength = 10;
	int m_intelligence = 10;
	int m_headshot = 10;

	STRENGTH_VALUES strengthValues;
	HEAL_VALUES healValues;
	HEADSHOT_VALUES headshotValues;

	SpriteObject characterSprite;
	sf::RectangleShape windowBackground;
	sf::RectangleShape characterHealth;
	sf::RectangleShape characterHealthBackground;
	sf::RectangleShape characterStamina;
	SpriteObject characterStrengthSprite;
	SpriteObject characterAgilitySprite;
	SpriteObject characterIntelligenceSprite;

public:


public:
	Enemy();
	Enemy(std::string identifier);
	Enemy(Scene& scene, sf::Font& font);
	~Enemy();
	void initializeVariablesEnemy();
};