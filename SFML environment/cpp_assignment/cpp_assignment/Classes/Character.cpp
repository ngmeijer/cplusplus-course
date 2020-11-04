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