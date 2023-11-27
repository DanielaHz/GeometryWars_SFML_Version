#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

/*
Brief Game:
This function call the Game constructor and pass by reference a config file.
In the context of the game this file is "config.txt".
*/
Game::Game(const std::string &config)
{
    init(config);
}

/*
Brief init:
This function handles the initialization of the game that includes:
- Open, read, parse and close data from the "config.txt" file.
- Save the data in respective structs variables.
- Create the SFML window.
- Call or spawn the player.
*/
void Game::init(const std::string &path)
{
    // Using ifstream to open files in the game
    std::ifstream data(path);
    if (!data.is_open())
    {
        // Display an error message if the file fails to open
        std::cerr << "failed to open the file " << std::endl;
        return;
    }

    // Read and parse data from the config file line by line
    std::string line;
    while (std::getline(data, line))
    {
        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        // Parse and save player configuration if the tag is "Player"
        if (tag == "Player")
        {
            iss >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S;
            iss >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB;
            iss >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB;
            iss >> m_playerConfig.OT >> m_playerConfig.V >> m_playerConfig.A;
        }

        // Parse and save enemy configuration if the tag is "Enemy"
        else if (tag == "Enemy")
        {
            iss >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX;
            iss >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT;
            iss >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
        }

        // Parse and save bullet configuration if the tag is "Bullet"
        else if (tag == "Bullet")
        {
            iss >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR;
            iss >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG;
            iss >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
        }
    }

    // Close the file after reading and parsing the data. Very important step!!
    data.close();

    // Creating the size of  the vindow game in SFML
    m_window.create(sf::VideoMode(1280, 720), "Geometry Wars SFML Version");
    m_window.setFramerateLimit(60);

    // Spawn the player.
    spawnPlayer();

    // Loading the font to use in the game

    if (!m_font.loadFromFile("C:/Users/ye-da/Assignment2-Done/font.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(50);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition((m_window.getSize().x / 2) - 4 * m_text.getCharacterSize(), 20.0f);

    if (!m_texture.loadFromFile("C:/Users/ye-da/Assignment2-Done/background.jpg"))
    {
        std::cout << "Fail to upload the background :(";
    }
}

/*
Brief run:
This function controls the game execution to achieve a consistent frame rate.
While the game is running, it calls various systems responsible for different aspects of the game.
*/

void Game::run()
{

    // Target time per frame for 60 FPS
    const sf::Time targetFrameTime = sf::seconds(1.0f / 60.0f);

    while (m_running)
    {
        // Get the time elapsed since the last frame
        sf::Time elapsedTime = frameClock.restart();

        // Limit the frame time to control the game speed
        if (elapsedTime < targetFrameTime)
        {
            // If the frame time is less than the target, slow down the game to achieve the target frame time
            sf::sleep(targetFrameTime - elapsedTime);
            elapsedTime = targetFrameTime;
        }

        // Update game entities with the elapsed time
        m_entities.update();

        // Call functions representing various systems in the game

        sEnemySpawner();        // Spawn enemies at predefined rate
        sMovement(elapsedTime); // handles player movement based on the elapsed time
        sCollision();           // Manages collisions between game entities
        sUserInput();           // Processes user input

        sRender();   // Renders the current state of the game
        sLifespan(); // Manages the lifespan of entities
    }
}

/*
Brief spawnPlayer:
This function create the player entity with a default components.
*/

void Game::spawnPlayer()
{
    // Creating and object player that points to the vector m_entities with the tag "Player"
    auto player = m_entities.addEntity("Player");

    // Setting the position of the player when the game start at center.x and center.y
    float mediumX = m_window.getSize().x / 2.0f;
    float mediumY = m_window.getSize().y / 2.0f;

    // Components to create the player
    player->cTransform = std::make_shared<CTransform>(Vec2(mediumX, mediumY), Vec2(m_playerConfig.S, m_playerConfig.S), 1.0f);
    player->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
    player->cInput = std::make_shared<CInput>();

    // Centralizes the player entity reference for easier access and management.
    m_player = player;
}

/*
Brief spawnEnemy:
This function creates an enemy entity with default components. The components are
configured based on data specified in the config.txt file and random data.
Note: Random data include Position, Vertices, Fill Color, and Speed.
*/
void Game::spawnEnemy()
{
    // Creating and object enemy that points to the vector m_entities with the tag "Enemy"
    auto enemy = m_entities.addEntity("Enemy");

    // Parameters configuration

    // Game window dimensions
    const int windowSizeX = 1280;
    const int windowSizeY = 720;

    // RGB color range
    const int maxRGB = 255;

    // Default angle
    const float angle = 1.0f;

    // 1. Random Value: Enemy Position.
    int randomPX = (rand() % (1 + windowSizeX));
    int randomPY = (rand() % (1 + windowSizeY));

    // 2. Random Value: Enemy Vertices.
    int randomV = m_enemyConfig.VMIN + (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));

    // 3. Random Value: Enemy Fill Color.
    int randomR = (rand() % (1 + maxRGB));
    int randomG = (rand() % (1 + maxRGB));
    int randomB = (rand() % (1 + maxRGB));

    // 4. Random Value: Enemy Speed.
    int randomS = m_enemyConfig.SMIN + (rand() % (1 + m_enemyConfig.SMAX - m_enemyConfig.SMIN));

    // Components to create the enemy.
    enemy->cTransform = std::make_shared<CTransform>(Vec2(randomPX, randomPY), Vec2(randomS, randomS), angle);
    enemy->cShape = std::make_shared<CShape>(m_enemyConfig.SR, randomV, sf::Color(randomR, randomG, randomB), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);
    enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
    enemy->cintLifespan = std::make_shared<CLifespan<int>>(5);
    enemy->cGeneratedData = std::make_shared<CGeneratedData>(randomV, m_enemyConfig.SR, randomR, randomG, randomB); // Component to save the random data created.
}

/*
Brief SpawnSmallEnemies:
This function creates smaller enemies positioned around the original entity.
Each small enemy is placed at an equal angle from the original entity.
*/

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // Get properties of the original enemy.
    auto originalShape = e->cGeneratedData;
    auto originalTransform = e->cTransform;

    // Geometry and Shape configuration small enemy.
    const int numVertices = originalShape->vertices;
    const float anglePerVertex = (2 * M_PI) / numVertices; // angle in radians.
    const int smallRadius = originalShape->radius / 2;
    const int radius = originalShape->radius;
    const int originalRed = originalShape->R;
    const int originalGreen = originalShape->G;
    const int originalBlue = originalShape->B;
    const int configRed = m_enemyConfig.OR;
    const int configGreen = m_enemyConfig.OG;
    const int configBlue = m_enemyConfig.OB;
    const int configOutlineThickness = m_enemyConfig.OT;

    for (int i = 1; i < numVertices + 1; ++i)
    {
        auto smallEnemy = m_entities.addEntity("SmallEnemy");

        // Adjust the angle for each small enemy to evenly distribute them around the original entity.
        float angleIncrement = anglePerVertex * i;

        // Relative position and velocity of the small enemy
        float offsetX = std::cos(angleIncrement) * radius;
        float offsetY = std::sin(angleIncrement) * radius;

        Vec2 position = originalTransform->pos + Vec2(offsetX, offsetY);
        Vec2 velocity = Vec2(offsetX, offsetY);

        // Components to create the small enemy
        smallEnemy->cTransform = std::make_shared<CTransform>(position, velocity, anglePerVertex);
        smallEnemy->cShape = std::make_shared<CShape>(smallRadius, numVertices, sf::Color(originalRed, originalGreen, originalBlue), sf::Color(configRed, configGreen, configBlue), configOutlineThickness);
        smallEnemy->cfloatLifespan = std::make_shared<CLifespan<float>>(0.1);
    }
}

/*
Brief spawnBullet:
This function is responsible for creating bullets that the player uses to
shoot enemies in the game. It utilizes the Simple and Fast Multimedia
Library (SFML) to handle shooting angles triggered by the right-click mouse event.
The function calculates the direction of the bullet based on the player's entity position
and the target coordinates.
*/
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target)
{
    auto bullet = m_entities.addEntity("Bullet");

    // Calculate the bullets spawn angle
    Vec2 direction = {(target.x - entity->cTransform->pos.x), (target.y - entity->cTransform->pos.y)};
    float angle = atan2(direction.x, direction.y);

    // Components to create a bullet
    bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos), Vec2(direction.x, direction.y), angle);
    bullet->cTransform->velocity = Vec2(direction.x, direction.y);
    bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
    bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
}

/*
Brief sMovement:
The sMovement function handles the movement logic for entities in the game, such as players,
enemies, bullets, and small enemies. It takes into account user input for player movement and
updates the positions of all entities based on their velocities and elapsed time.
*/
void Game::sMovement(sf::Time elapsedTime)
{
    // Constants for player position constraint and window size
    const float playerRadius = 32.0f;
    const float windowSizeX = 1280.0f;
    const float windowSizeY = 720.0f;

    // Player movement
    for (auto e : m_entities.getEntities("Player"))
    {

        // Store original velocities for later reference
        float originalVelocityX = e->cTransform->velocity.x;
        float originalVelocityY = e->cTransform->velocity.y;

        // Reset velocity before processing new input
        e->cTransform->velocity = {0, 0};

        // Process user input for player movement
        if (e->cInput->up)
            e->cTransform->velocity.y += -1.0f;
        else if (e->cInput->down)
            e->cTransform->velocity.y += 1.0f;
        else if (e->cInput->right)
            e->cTransform->velocity.x += 1.0f;
        else if (e->cInput->left)
            e->cTransform->velocity.x += -1.0f;

        // player position limit.
        e->cTransform->pos.x = std::clamp(e->cTransform->pos.x, playerRadius, windowSizeX - playerRadius);
        e->cTransform->pos.y = std::clamp(e->cTransform->pos.y, playerRadius, windowSizeY - playerRadius);

        // Movement update
        e->cTransform->pos.x += e->cTransform->velocity.x * elapsedTime.asSeconds();
        e->cTransform->pos.y += e->cTransform->velocity.y * elapsedTime.asSeconds();
    }

    // Enemy Movement and Position Update
    for (auto e : m_entities.getEntities("Enemy"))
    {
        // Reflect enemy at window boundaries
        if (e->cTransform->pos.x <= m_enemyConfig.SR || e->cTransform->pos.x >= windowSizeX - playerRadius)
        {
            e->cTransform->velocity.x *= -1;
        }
        else if (e->cTransform->pos.y <= playerRadius || e->cTransform->pos.y >= windowSizeY - playerRadius)
        {
            e->cTransform->velocity.y *= -1;
        }

        // Movement update
        e->cTransform->pos.x += e->cTransform->velocity.x * elapsedTime.asSeconds();
        e->cTransform->pos.y += e->cTransform->velocity.y * elapsedTime.asSeconds();
    }

    // Bullet Position Update
    for (auto e : m_entities.getEntities("Bullet"))
    {
        // Movement update
        e->cTransform->pos.x += e->cTransform->velocity.x * elapsedTime.asSeconds();
        e->cTransform->pos.y += e->cTransform->velocity.y * elapsedTime.asSeconds();
    }

    // SmallEnemy Position Update
    for (auto e : m_entities.getEntities("SmallEnemy"))
    {
        // Movement update
        e->cTransform->pos.x += e->cTransform->velocity.x * elapsedTime.asSeconds();
        e->cTransform->pos.y += e->cTransform->velocity.y * elapsedTime.asSeconds();
    }
}

/*
Brief sCollision:
The sCollision function handles collision detection between enemy entities and player bullets.
When a collision is detected, it triggers the destruction of both the enemy and the bullet.
Additionally, it spawns small enemies as a result of the collision.
*/
void Game::sCollision()
{

    // Iterate through enemies
    for (auto e : m_entities.getEntities("Enemy"))

    {
        // Iterate through bullets
        for (auto b : m_entities.getEntities("Bullet"))
        {
            // Get positions and calculate distance
            Vec2 positionBullet = b->cTransform->pos;
            Vec2 positionEnemy = e->cTransform->pos;
            float distanceBetween = positionBullet.dist(positionEnemy);

            // Calculate sum of collision radius
            float sumRadioCollision = b->cCollision->radius + e->cCollision->radius;

            // Check for collision
            if (distanceBetween < sumRadioCollision)
            {
                // Destroy the enemy and spawn smaller enemies
                e->destroy();
                spawnSmallEnemies(e);

                // Destroy the bullet
                b->destroy();
            }
        }
    }
}

/*
Brief sLifespan:
The sLifespan function manages the lifespan of enemy entities and small enemy entities.
It checks the elapsed time since their creation against their specified lifespan and destroys
entities that have exceeded their lifespan.
*/
void Game::sLifespan()
{
    // Iterate through enemies
    for (auto e : m_entities.getEntities("Enemy"))
    {
        // Get elapsed time and total lifespan for "Enemy"
        int elapsed = static_cast<int>(e->cintLifespan->lifeClock.getElapsedTime().asSeconds());
        int totalEnemy = e->cintLifespan->total;

        // Check if elapsed time exceeds total lifespan
        if (elapsed >= totalEnemy)
        {
            // Destroy the enemy
            e->destroy();
        }
    }

    // Iterate through small enemies
    for (auto se : m_entities.getEntities("SmallEnemy"))
    {
        // Get elapsed time and total lifespan for "SmallEnemy"
        float elapsed = (se->cfloatLifespan->lifeClock.getElapsedTime().asSeconds());
        float totalEnemy = se->cfloatLifespan->total;

        // Check if elapsed time exceeds total lifespan
        if (elapsed >= totalEnemy)
        {
            // Destroy the small enemy
            se->destroy();
        }
    }
}

/*
Brief sEnemySpawner:
The sEnemySpawner function manages the spawning of enemy entities at a specified
interval. It uses a clock to track the elapsed time and spawns an enemy when the
interval is reached.

*/
void Game::sEnemySpawner()
{
    // Set the time interval for enemy spawning
    const int enemySpawnInterval = 2;

    // Get the elapsed time since the last spawn
    int elapsed = static_cast<int>(spawnerClock.getElapsedTime().asSeconds());

    // Check if it's time to spawn a new enemy
    if (elapsed >= enemySpawnInterval)
    {
        spawnEnemy();           // Spawn a new enemy
        spawnerClock.restart(); // Restart the spawner clock for the next interval
    }
}

/*
Brief sRender:
The sRender function manages the rendering of entities in the game. It clears
the window, draws the background and text, and then renders each entity by
updating their positions and shapes.
*/
void Game::sRender()
{

    // Clear the game window
    m_window.clear();

    // Draw the background and text
    m_window.draw(background);
    m_window.draw(m_text);

    // Iterate through all entities
    for (auto e : m_entities.getEntities())
    {

        // Calculate the position of the entity
        float posX = e->cTransform->pos.x;
        float posY = e->cTransform->pos.y;

        // Set the position of the shape in the entity
        e->cShape->circle.setPosition(posX, posY);

        // Rotate the shape for visual interest
        float angle = 0.2f * (M_PI / 180);
        e->cShape->circle.rotate(angle);

        // Draw the shape of the entity
        m_window.draw(e->cShape->circle);
    }

    // Display the rendered content
    m_window.display();
}

/*
Brief sUserInput:
The sUserInput function manages user input events, such as key presses,
key releases, and mouse button presses. It updates the game state based on user interactions, including player movement and bullet spawning.
*/
void Game::sUserInput()
{
    sf::Event event;

    // Process all pending events
    while (m_window.pollEvent(event))
    {
        // Check if the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        // Set the title of the window
        m_text.setString("GEOMETRY WARS");

        // Scale the background to fit the game window
        float scaleX = static_cast<float>(m_window.getSize().x / static_cast<float>(m_texture.getSize().x));
        float scaleY = static_cast<float>(m_window.getSize().y / static_cast<float>(m_texture.getSize().y));
        background.setTexture(m_texture);
        background.setScale(scaleX, scaleX);

        // this event is triggered when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case ::sf::Keyboard::W:
                std::cout << "W key Pressed\n";
                m_player->cInput->up = true;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::S:
                std::cout << "S key Pressed\n";
                m_player->cInput->down = true;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::A:
                std::cout << "A key Pressed\n";
                m_player->cInput->left = true;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::D:
                std::cout << "W key Pressed\n";
                m_player->cInput->right = true;
                break;
            default:
                break;
            }
        }

        // Check for key releases
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case ::sf::Keyboard::W:
                std::cout << "W key Pressed\n";
                m_player->cInput->up = false;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::S:
                std::cout << "S key Pressed\n";
                m_player->cInput->down = false;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::A:
                std::cout << "A key Pressed\n";
                m_player->cInput->left = false;
                break;
            default:
                break;
            }

            switch (event.key.code)
            {
            case ::sf::Keyboard::D:
                std::cout << "W key Pressed\n";
                m_player->cInput->right = false;
                break;
            default:
                break;
            }
        }

        // Check for mouse button presses
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Spawn a bullet at the mouse click position
                Vec2 target(event.mouseButton.x, event.mouseButton.y);
                spawnBullet(m_player, target);
            }
        }
    }
}
