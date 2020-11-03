#include "../Headers/Character.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

Character::Character() {

}

Character::~Character() { }

int Character::GenerateValues(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(min, max);

	int value = distr(gen);

	return value;
}

void Character::drawPlayerScreen() {

}

int Character::getStrength()
{
	std::cout << "calling getStrength method" << std::endl;
	std::string line;
	std::ifstream myfile("PlayerData.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n';
		}
		myfile.close();
	}
	else std::cout << "Unable to open file" << std::endl;

	//int value = std::stoi(line);


	return 0;
}

int Character::getAgility()
{
	return 0;
}

int Character::getIntelligence()
{
	return 0;
}
