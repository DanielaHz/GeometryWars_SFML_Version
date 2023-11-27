#pragma once

#include "Entity.h"
#include "EntityManager.h"

#ifndef M_PI
#define M_PI (std::acos(-1.0))
#endif

struct PlayerConfig
{
    int SR, CR;
    int S;
    int FR, FG, FB, OR, OG, OB, OT, V, A;
};
struct EnemyConfig
{
    int SR, CR;
    int SMIN, SMAX;
    int OR, OG, OB, OT, VMIN, VMAX, L, SI;
};
struct BulletConfig
{
    int SR, CR;
    int S;
    int FR, FG, FB, OR, OG, OB, OT, V, L;
};

class Game
{
    sf::RenderWindow m_window; // the window we will draw to
    EntityManager m_entities;  // vector of entities to maintain
    sf::Font m_font;           // the font we will use to draw
    sf::Text m_text;           // the score text to be drawn to the screen
    sf::Texture m_texture;
    sf::Sprite background;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    sf::Clock totalGameTimeClock; // Control total game time
    sf::Clock frameClock;         // Object that measure time intervals
    sf::Clock spawnerClock;

    int m_score = 0;
    bool m_paused = false; // whether we update game logic
    bool m_running = true; // whether the game is running

    std::shared_ptr<Entity> m_player;

    void init(const std::string &config); // initialize the GameState with a config file path
    void setPaused(bool paused);          // pause the game

    void Score(std::shared_ptr<Entity> e);
    void sMovement(sf::Time x); // System: Entity position / movement update
    void sUserInput();          // System: User Input
    void sLifespan();           // System: Lifespan
    void sRender();             // System: Render / Drawing
    void sEnemySpawner();       // System: Spawns Enemies
    void sCollision();          // System: Collisions

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string &config); // constructor, takes in game config
    void run();
    int getScore() const { return m_score; }
};
