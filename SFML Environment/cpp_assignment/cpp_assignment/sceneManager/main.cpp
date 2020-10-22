#include <SFML/Graphics.hpp>

#include "scene.hpp"
#include "spriteObject.hpp"
#include "sceneHandler.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML with Scenes!");
    Scene mainMenu("menu");

    

    SpriteObject sprite1("soldierSprite", "head.png");
    sprite1.setPosition(sf::Vector2f(70.0f, 70.0f));
    sprite1.setScale(sf::Vector2f(5.0f, 5.0f));
    mainMenu.addGameObject(sprite1);

    //Scene characterSelect("scene02");

    //SpriteObject sprite2("soldierSprite", "head_hurt.png");
    //sprite2.setPosition(sf::Vector2f(70.0f, 70.0f));
    //sprite2.setScale(sf::Vector2f(5.0f, 5.0f));
    //characterSelect.addGameObject(sprite2);

    SceneHandler handler;
    handler.addScene(mainMenu);
    //handler.addScene(characterSelect);

    int counter = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                /*if(event.key.code == sf::Keyboard::A) {
                    if(counter == 0) {
                        handler.stackScene("scene02");
                        counter++;
                    } else {
                        handler.popScene();
                        counter--;
                    }
                }*/
            }
        }
        window.clear();
        handler.update();
        handler.render(window);
        window.display();
    }

    return 0;
}





