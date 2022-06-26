#pragma once
#include <SFML/Graphics.hpp>

template <typename T, typename R>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x * r.x;
    T Y = left.y * r.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T, typename R>
sf::Vector2<T> operator /(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x / r.x;
    T Y = left.y / r.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T, typename R>
sf::Vector2<T> operator +(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x + r.x;
    T Y = left.y + r.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T, typename R>
sf::Vector2<T> operator -(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x - r.x;
    T Y = left.y - r.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T, typename R>
void operator -=(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x -= r.x;
    T Y = left.y -= r.y;
}

template <typename T, typename R>
void operator +=(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x += r.x;
    T Y = left.y += r.y;
}

template <typename T, typename R>
void operator /=(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x /= r.x;
    T Y = left.y /= r.y;
}

template <typename T, typename R>
void operator *=(const sf::Vector2<T>& left, const sf::Vector2<R>& right)
{
    auto r = sf::Vector2<T>(right);
    T X = left.x *= r.x;
    T Y = left.y *= r.y;
}



#define PI M_PI
using namespace sf;

float mag(sf::Vector2<float> &vec) {
    return sqrt(pow(vec.x, 2)+pow(vec.y, 2));
}

sf::Vector2<float> mouse2screen(sf::RenderWindow* window) {
    auto m = sf::Mouse::getPosition();
    m.y-=30;
    auto c = sf::Vector2<float>(window->getPosition());
    return sf::Vector2<float>(m-c);
}
