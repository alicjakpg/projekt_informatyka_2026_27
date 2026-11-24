#include <SFML/Graphics.hpp>
#include <array> 

class Stone : public sf::RectangleShape {
    private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;

    public:
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar,
    int L)
        : m_punktyZycia(L), m_jestZniszczony(false)
    {
        this->setPosition(startPos);
        this->setSize(rozmiar);
        this->setOutlineThickness(2.f);
        aktualizujKolor();
    }

    void trafienie() {
        if (m_jestZniszczony == true)
        return;

        m_punktyZycia--;
        aktualizujKolor();

        if (m_punktyZycia <= 0)
        m_jestZniszczony = true;
    }
void aktualizujKolor() {
    if (m_punktyZycia >= 0 && m_punktyZycia < 4) {
        this->setFillColor(m_colorLUT[m_punktyZycia]);
    }
}

bool isDestroyed() const {
    return m_jestZniszczony;
}

void draw(sf::RenderTarget &target) const {
    if (m_jestZniszczony == false) {
        target.draw(*this);
    }
}
};
inline const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue

};



