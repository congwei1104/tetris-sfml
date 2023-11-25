
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
class Game {
  public:
    sf::RenderWindow window;

    Game() { window.create({320, 480}, "hello"); }

    void handleInput() {}

    void update() {}

    void render() {}
};
