#include "SFML/Graphics/Color.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>

int main() {
    Game game;

    while (game.window.isOpen()) {

        // 1. 事件处理
        game.handleInput();

        // 2. 更新物理逻辑
        game.update();

        // 3. 渲染
        game.window.clear(sf::Color::White);
        game.render();
        game.window.display();
    }
    return 0;
}