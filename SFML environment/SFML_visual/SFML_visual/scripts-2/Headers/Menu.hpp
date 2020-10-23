#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/scene.hpp"
#include "../Headers/gameObject.hpp"

using namespace sf;

const int maxText = 3;

class Menu : public GameObject
{
public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void render(RenderWindow& window);
	void update() override;
	void defineButtons();
	void checkInput(RenderWindow& window);

private:
	Font font;
	Text menuText[maxText];
};

