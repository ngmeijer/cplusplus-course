#pragma once
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"

class Character : public GameObject
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

	sf::Text characterStrengthText;
	sf::Text characterAgilityText;
	sf::Text characterIntelligenceText;
	sf::Text characterName;

	sf::Font m_font;
	sf::Vector2f m_characterPosition;
	sf::RectangleShape windowBackground;
	sf::RectangleShape characterHealth;
	sf::RectangleShape healthBackground;
	sf::RectangleShape characterStamina;
	sf::RectangleShape staminaBackground;

	SpriteObject characterSprite;
	SpriteObject strengthSprite;
	SpriteObject agilitySprite;
	SpriteObject intelligenceSprite;

	std::string m_spriteName;
	std::string m_characterName;

	Scene m_scene;

	sf::Vector2f windowBackgroundPos;
	sf::Vector2f characterSpritePos;
	sf::Vector2f characterHealthPos;
	sf::Vector2f healthBackgroundPos;
	sf::Vector2f characterStaminaPos;
	sf::Vector2f staminaBackgroundPos;
	sf::Vector2f strengthSpritePos;
	sf::Vector2f agilitySpritePos;
	sf::Vector2f intelligenceSpritePos;

	sf::Vector2f strengthTextPos;
	sf::Vector2f agilityTextPos;
	sf::Vector2f intelligenceTextPos;
	sf::Vector2f characterNamePos;

public:
	Character();
	Character(std::string identifier);
	~Character();
	virtual void render(sf::RenderWindow& window);
	virtual void update();
	void handleCharacter(Scene& scene);
	void handleCharacterText(Scene& scene);
	void handleCharacterSprites(Scene& scene);
};