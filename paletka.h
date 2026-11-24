#include <SFML/Graphics.hpp>

class Paletka {
    private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;

    public:
    Paletka(float sx, float sy, float sszerokosc, float swysokosc, float spredkosc ){
        x = sx;
        y = sy;
        szerokosc = sszerokosc;
        wysokosc = swysokosc;
        predkosc = spredkosc;

        shape.setSize({szerokosc, wysokosc});
        shape.setOrigin({szerokosc / 2, wysokosc / 2});
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::Cyan);
 }
void moveLeft(){
    x = x - predkosc;
    shape.setPosition({x,y});

}

void moveRight() {
    x = x + predkosc;
    shape.setPosition({x,y});
}

void clampToBounds(float width) {
    if (x - szerokosc /2 <0 ){
        x = szerokosc /2;
        shape.setPosition({x,y});
    }
    if (x + szerokosc /2 > width) {
        x = width - szerokosc /2;
        shape.setPosition({x,y});
    }
}
    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

float getX() const {return x;}
float getY() const {return y;}
float getSzerokosc() const { return szerokosc ;}
float getWysokosc() const {return wysokosc;}


};