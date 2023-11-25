
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <iostream>

class Game {
  public:
    sf::RenderWindow window;

    sf::Sprite s;
    sf::Texture t;

    Game() {
        window.create({320, 480}, "Tetris");

        if (!t.loadFromFile("images/tiles.png")) {
            std::cerr << "Unable to load image! \n";
        }
        s.setTexture(t);
        s.setTextureRect(sf::IntRect(0, 0, 18, 18));
    }

    void handleInput() {}

    void update() {}

    void render() { window.draw(s); }
};
