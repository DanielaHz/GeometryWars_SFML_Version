# GEOMETRY WARS SFML VERSION 

This C++ program is a rendition of the popular game Geometry Wars using the Simple and Fast Multimedia Library (SFML). The game leverages an Entity-Component-System (ECS) design pattern to separate architecture concerns, simplifying game development.

## ECS Arquitecture

1. **Entities:**
   - Player
   - Enemy
   - SmallEnemy
   - Bullets

2. **Components:**
   - **CTransform:** Manages the position, velocity, and angle of entities.
   - **CShape:** Handles data for drawing entities. SFML is used as the graphic interface, incorporating parameters such as radius, vertices, color, etc.
   - **CCollision:** Manages the collision radius of entities.
   - **CScore:** Handles the score, considering the vertices of the figure.
   - **CLifespan:** Stores the duration or lifespan in frames for each entity.
   - **CInput:** Initializes keyboard inputs in the game: up, down, right, left, shoot.

3. **Systems:**
   - **sEnemySpawner():** Spawns enemies at a predefined rate.
   - **sMovement(elapsedTime):** Handles player movement based on elapsed time.
   - **sCollision():** Manages collisions between game entities.
   - **sUserInput():** Processes user input.
   - **sRender():** Renders the current state of the game.
   - **sLifespan():** Manages the lifespan of entities.

## Code Structure

### Components.h
The Components class defines and stores data for various entities in the game. It consists of six components, including CTransform for managing entity positions and angles, CShape for handling drawing information using SFML, CCollision for collision radius, CScore for scoring based on figure vertices, CLifespan for tracking entity lifespan, and CInput for initializing keyboard inputs such as movement and shooting.

### Entity.cpp
The Entity class represents interactive elements in the game, such as Player, Enemy, Bullet, and SmallEnemy. This class implements methods for checking entity activity (IsActive()), retrieving the entity's tag type (tag()), obtaining its unique identifier (id()), and managing its status through the destroy() method, which marks the entity as inactive without actually destroying it.

### Entity.h
The Entity class, designed as a friend class to EntityManager, defines the attributes of game entities. It uses shared pointers to link components, ensuring automatic memory management. This class encapsulates the creation and manipulation of entities, providing methods for initialization, updating, retrieval, and removal. EntityManager is responsible for coordinating and organizing these entities within the game.

### EntityManager.cpp
The EntityManager class manages the creation, update, and removal of entities in the game. The Update() function processes a buffer vector, m_entitiesToAdd, updating the main entity vector (m_entities) and a map (m_entityMap) using entity tags as keys. The RemoveDeadEntities() function removes entities marked as inactive, utilizing the std::remove_if algorithm. Additional functions include addEntity() for adding new entities, getEntities() for retrieving all entities, and getEntities(&tag) for obtaining entities based on their tags.

### EntityManager.h
The EntityManager class definition includes vectors (m_entities and m_entitiesToAdd), a map (m_entityMap), and a counter for the total number of entities (m_totalentities). Methods include RemoveDeadEntities(), Update(), addEntity(), getEntities(), getEntities(&tag), and getEntityMap(). This class facilitates the organization and management of entities within the game.

### Game.cpp
The Game class initializes the game, reads configuration data from the "config.txt" file, and handles various parameters for players, enemies, and bullets. The constructor calls an initialization function (init()) with a string parameter, typically representing the configuration file. The Game class serves as the entry point for setting up the game and managing its overall structure.

### Game.h
The Game class orchestrates the core functionalities of the game. It manages the game window, entities, user input, rendering, and spawning using various systems. Key attributes include the window, entity manager, font, and configuration structs for player, enemy, and bullets. Time clocks regulate game timing. Systems handle movement, user input, lifespan, rendering, enemy spawning, and collisions. Methods for spawning entities include players, enemies, small enemies, bullets, and special weapons. The game is initialized with a configuration file, and the run method executes the game loop. The class provides methods to pause and retrieve the score.

### main.cpp
The main function initializes an instance of the Game class, passing the configuration file path "config.txt." It then calls the run method, which executes the main game loop. The program returns 0 upon completion, indicating successful execution.

### Vec2.cpp
The Vec2 class represents a 2D vector and provides essential operations commonly used in vector mathematics. The class contains a default constructor and a parameterized constructor for creating instances of 2D vectors. Overloaded operators enable arithmetic operations such as addition, subtraction, multiplication, and division, both in scalar and vector forms.

### Vec2.h
The Vec2 class represents a 2D vector and serves as a fundamental building block for mathematical operations in the program. The class includes default and parameterized constructors for creating instances of 2D vectors with specified coordinates. Two public attributes, x and y, hold the vector's components.

## Game Logic Overview
In the game, the player starts in the middle of the window and can move in four directions using the W, A, S, and D keys. The player shoots bullets towards the mouse pointer when the left mouse button is clicked. Enemies spawn every 2 seconds with random properties like size and speed. When the player defeats an enemy, it explodes and gives birth to a specific number of smaller enemies, positioned based on the original enemy's vertices. This dynamic spawning adds a layer of strategy to the game. Both the player and enemies are confined within the game window, contributing to the overall challenge and engagement of the gameplay.

## Dependencies 
- SFML library 
- Font file: font.ttf
- Background file: background.jpg
- Makefile

