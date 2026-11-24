#include "Game.h"
#include <iostream>
#include <optional>
#include <algorithm>

Game::Game()
    : m_window(sf::VideoMode({640, 480}), "Arkanoid test"),
      m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
      m_pilka(320.f, 300.f, 4.f, 3.f, 8.f)
{
    m_window.setFramerateLimit(60);

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + 2.f);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_paletka.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_paletka.moveRight();
    }
    m_paletka.clampToBounds(WIDTH);

    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    for (auto& stone : m_bloki) {
        if (!stone.isDestroyed()) {
            float bx = stone.getPosition().x;
            float by = stone.getPosition().y;
            float bw = stone.getSize().x;
            float bh = stone.getSize().y;

            if (m_pilka.getX() + m_pilka.getRadius() >= bx &&
                m_pilka.getX() - m_pilka.getRadius() <= bx + bw &&
                m_pilka.getY() + m_pilka.getRadius() >= by &&
                m_pilka.getY() - m_pilka.getRadius() <= by + bh)
            {
                stone.trafienie();
                m_pilka.bounceY();
                m_pilka.move();
                break;
            }
        }
    }

    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Stone& s) { return s.isDestroyed(); }),
        m_bloki.end()
    );

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_window.close();
    }
}

void Game::render() {
    m_window.clear(sf::Color(20, 20, 30));
    for (auto& stone : m_bloki) {
        stone.draw(m_window);
    }
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);
    m_window.display();
}

