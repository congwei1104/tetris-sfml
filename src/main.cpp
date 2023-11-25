#include "SFML/Window/Event.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>

int main() {

    Game game;

    sf::Clock clock;
    sf::Time elapsed;

    float frametime = 1.0f / 60.0f;

    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.window.close();
            }
        }

        // 1. 事件处理
        game.handleInput();

        // 2. 更新物理逻辑
        if (elapsed.asSeconds() >= frametime) {
            elapsed -= sf::seconds(frametime);
            game.update(); // 60次/秒
        }
        elapsed += clock.restart();

        // 3. 渲染
        game.window.clear();
        game.render();
        game.window.display();
    }

    return 0;
}