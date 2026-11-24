#include <SFML/Graphics.hpp>
#include <cmath>
#include "paletka.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float sx, float sy, float svx, float svy, float sr) {
        x = sx;
        y = sy;
        vx = svx;
        vy = svy;
        radius = sr;

        shape.setRadius(radius);
        shape.setOrigin({radius, radius});
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::White);
    }

void move() {

    x += vx;
    y += vy;
    shape.setPosition({x, y});
}

void bounceX() {
    vx = -vx;
}
 
void bounceY() {
    vy= -vy;
}

void collideWalls(float width, float height) {
    if (x - radius <= 0) {
        bounceX();
        x = radius;
        shape.setPosition({x, y});
    }
    if (x + radius >= width) {
        bounceX();
        x = width - radius;
        shape.setPosition({x, y});
    }
    if (y - radius <= 0) {
        bounceY();
        y = radius;
        shape.setPosition({x, y});
    }
}


bool collidePaddle( const Paletka& pal) {
    float palX = pal.getX();
    float palY = pal.getY();
    float palW = pal.getSzerokosc();
    float palH = pal.getWysokosc();


    if (x >= palX - palW / 2 && x <= palX + palW /2) {
        if ((y + radius) >= (palY - palH /2) && (y - radius) < (palY - palH /2)) {

            vy = -std::abs(vy);
            y = (palY - palH /2) - radius;
            shape.setPosition({x, y});
            return true;
        }
    }
    return false;
}

void draw(sf::RenderTarget& target) {
    target.draw(shape);
}

float getX() const { return x; }
float getY() const { return y; }
float getVx() const { return vx; }
float getVy() const { return vy; }
float getRadius() const { return radius; }
};