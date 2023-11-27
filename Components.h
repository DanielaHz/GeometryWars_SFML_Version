#pragma once

#include "Vec2.h"

#include <SFML/Graphics.hpp>

// COMPONENTS ESC ARCHITECTURE

// *Components are properties attached to entities.They are responsable to store only data* .

class CTransform
// Component that handle the entitie's position, velocity and angle.
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0;

    CTransform(const Vec2 &p, const Vec2 &v, float a)
        : pos(p), velocity(v), angle(a) {}
};

class CShape
// Component that handle information to draw entities in the SFML window
// using SFML library functionalities.
{
public:
    sf::CircleShape circle;

    CShape(float radius, int points, const sf::Color &fill, const sf::Color &outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision
// Component that handle the collision of the entities.
{
public:
    float radius = 0;
    CCollision(float r)
        : radius(r) {}
};

class CScore
// Component that handle the score.
{
public:
    const int score = 0;
    CScore(const int s)
        : score(s) {}
};

template <typename T>
class CLifespan
// Component that handle the lifespan.
{
public:
    // sf::Time creationTime; // amount of lifespan remaining on the entity
    T total; // the total initial amount of lifespan
    sf::Clock lifeClock;
    CLifespan(T t)
        : total(t) {}
};

class CInput
// Component that handle the user inputs to move the player entity.
{
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;

    CInput() {}
};

class CGeneratedData
// Component to handle the creation of smallEntities when the Big one collides.
// Some kind of components of the parent entites are generated in the game.
{
public:
    int vertices = 3; // random vertices generate for the original enemy
    int radius = 0;   // random radius
    int R = 0;        // random color RGB data
    int G = 0;
    int B = 0;

    CGeneratedData(int &v, int &rd, int &r, int &g, int &b)
        : vertices(v), radius(rd), R(r), G(g), B(b) {}
};
