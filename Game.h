#include <SFML/Graphics.hpp>
#include <vector>
#include "pilka.h"
#include "Stone.h"

class Game {
private:
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow m_window;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};
