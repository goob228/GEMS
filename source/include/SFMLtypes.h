#ifndef SFMLTYPES_H
#define SFMLTYPES_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"



typedef sf::Vector2i iVector2;

typedef sf::Vector2f fVector2;

typedef sf::RectangleShape RectangleShape;

namespace Color {
    inline const auto White  = sf::Color::White;
    inline const auto Black  = sf::Color::Black;
    inline const auto Red    = sf::Color::Red;
    inline const auto Blue   = sf::Color::Blue;
    inline const auto Yellow = sf::Color::Yellow;
    inline const auto Magenta= sf::Color::Magenta;
    inline const auto Green  = sf::Color::Green;
    inline const auto Cyan   = sf::Color::Cyan;
    inline const auto Gray   = sf::Color(150,150,150);
}

#endif