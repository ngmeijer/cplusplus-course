#pragma once
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"

class Character : public GameObject
{
private:
	struct STRENGTH_VALUES {
		int strength3 = 25;
		int strength4 = 35;
		int strength5 = 50;
		int strength6 = 65;
		int strength7 = 75;
		int strength8 = 85;
		int strength9 = 100;
		int strength10 = 115;
	};

	struct HEAL_VALUES {
		int heal3 = 35;
		int heal4 = 50;
		int heal5 = 75;
		int heal6 = 100;
		int heal7 = 125;
		int heal8 = 150;
		int heal9 = 175;
		int heal10 = 200;
	};

	struct HEADSHOT_VALUES {
		int headshot3 = 35;
		int headshot4 = 45;
		int headshot5 = 60;
		int headshot6 = 85;
		int headshot7 = 125;
		int headshot8 = 150;
		int headshot9 = 175;
		int headshot10 = 200;
	};

public:
	int m_strength = 10;
	int m_heal = 10;
	int m_headshot = 10;

	STRENGTH_VALUES strengthValues;
	HEAL_VALUES healValues;
	HEADSHOT_VALUES headshotValues;

	sf::Text characterStrengthText;
	sf::Text characterHealText;
	sf::Text characterHeadshotText;
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
	SpriteObject healSprite;
	SpriteObject headshotSprite;

	std::string m_spriteName;
	std::string m_characterName;
	std::string* characterNamePtr;

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

	sf::Vector2f healthSize = sf::Vector2f(480, 10);
	sf::Vector2f staminaSize = sf::Vector2f(480, 10);

public:
	Character();
	Character(std::string identifier);
	~Character();
	virtual void render(sf::RenderWindow& window);
	virtual void update();



	//Initiliazation
	void handleCharacter(Scene& scene);
	void handleCharacterText(Scene& scene);
	void handleCharacterSprites(Scene& scene);
	void importStats(int p_strength, int p_headshot, int p_intelligence);

	//Actions
	int generateCharacterSkill(int min, int max);
	void generateCharacter();
	void receiveRegDamage(int damageTaken);
	void handleStamina(int amount);
	bool checkStamina(int staminaSpent);
	bool canHealSelf(int staminaSpent, int healAmount);
	void receiveHeadshot(int damageTaken);
	bool isDead();
	std::string returnCharacterName();
	void findNextDemon();
	void resetCharacterStats();
};