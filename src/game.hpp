
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class Game {
  public:
    sf::RenderWindow window;

    sf::Sprite s;
    sf::Texture t;

    static const int M = 20;
    static const int N = 10;
    std::vector<std::vector<int>> field;
    int figures[7][4] = {
        {1, 3, 5, 7}, // I
        {2, 4, 5, 7}, // Z
        {3, 5, 4, 6}, // S
        {3, 5, 4, 7}, // T
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4, 5}  // O
    };

    struct Point {
        int x;
        int y;
    } a[4], b[4];

    sf::Clock clock;
    sf::Time elapsed;

    // 左右移动
    int dx = 0;
    bool rotatable = false;

    int colorNum = 1;

    Game() {
        window.create({320, 480}, "Tetris");

        field.resize(M, std::vector<int>(N, 0));

        if (!t.loadFromFile("images/tiles.png")) {
            std::cerr << "Unable to load image! \n";
        }
        s.setTexture(t);
        s.setTextureRect(sf::IntRect(0, 0, 18, 18));

        for (int i = 0; i < 4; i++) {
            a[i].x = figures[3][i] % 2;
            a[i].y = figures[3][i] / 2;
        }

        srand(time(0));
    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    dx = -1;
                } else if (event.key.code == sf::Keyboard::Right) {
                    dx = 1;
                } else if (event.key.code == sf::Keyboard::Up) {
                    rotatable = true;
                }
            }
        }
    }

    void update() {
        float framtime = 1.0 / 3.0f;
        if (elapsed.asSeconds() >= framtime) {
            elapsed -= sf::seconds(framtime);

            moveDown();
        }
        elapsed += clock.restart();

        // 左右移动
        if (dx) {
            moveX();
        }

        // 旋转
        if (rotatable) {
            rotate();
        }
    }

    void render() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;
                s.setPosition(j * 18, i * 18);
                window.draw(s);
            }
        }

        for (int i = 0; i < 4; i++) {
            s.setPosition(a[i].x * 18, a[i].y * 18);
            window.draw(s);
        }
    }

    void rotate() {
        Point p = a[1]; // 旋转中心
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (!canMove()) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }
        rotatable = false;
    }

    void moveDown() {
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].y += 1;
        }

        if (!canMove()) {
            for (int i = 0; i < 4; i++) {
                field[b[i].y][b[i].x] = colorNum;
            }

            colorNum = 1 + rand() % 7;
            int n = rand() % 7;
            for (int i = 0; i < 4; i++) {
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }
    }

    void moveX() {
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!canMove()) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }
        dx = 0;
    }

    bool canMove() {
        for (int i = 0; i < 4; i++) {
            if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
                return false;
            } else if (field[a[i].y][a[i].x]) {
                return false;
            }
        }
        return true;
    }
};
