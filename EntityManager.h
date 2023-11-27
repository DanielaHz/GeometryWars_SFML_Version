#pragma once

#include "Entity.h"

#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVec; // Vector to store entites
typedef std::map<std::string, EntityVec> EntityMap;     // Map that store the entities by tag eje: "Player", "Enemy", "SmallEnemy" , "Bullet"

class EntityManager
{
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;

    void removeDeadEntities(EntityVec &vec);

public:
    EntityManager();

    void update();

    // Member access functions or methods declarations.
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    const EntityVec &getEntities();
    const EntityVec &getEntities(const std::string &tag);
    const std::map<std::string, EntityVec> &getEntityMap();
};
