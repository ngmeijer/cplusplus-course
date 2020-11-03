#pragma once
class Character
{
public:
	int m_strength = 10;
	int m_agility = 10;
	int m_intelligence = 10;

public:
	int GenerateValues(int min, int max);

public:
	Character();
	~Character();
	void drawPlayerScreen();
	int getStrength();
	int getAgility();
	int getIntelligence();
};