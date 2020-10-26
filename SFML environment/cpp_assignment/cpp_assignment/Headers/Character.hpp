#pragma once
class Character
{
public:
	int strength = 100;
	int agility = 100;
	int intelligence = 100;

public:
	int GenerateValues(int min, int max);

public:
	Character();
	~Character();
};