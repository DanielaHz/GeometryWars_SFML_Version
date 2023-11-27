
#include "EntityManager.h"

#include <algorithm>

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    for (auto e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    // remove dead entities from the vector of all entities
    removeDeadEntities(m_entities);

    // remove dead entities from each vector in the entity map
    // c++17 way of iterating through [key,value] pairs in a map
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{

    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const auto &e)
                             { return !e->m_active; }),
              vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{

    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_entitiesToAdd.push_back(entity);
    return entity;
}

const EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag)
{
    auto ittag = m_entityMap.find(tag);
    if (ittag != m_entityMap.end())
    {
        return ittag->second;
    }
    else
    {
        // if the tag its not in the game it return an empty vector
        static EntityVec emptyEntityVec; // Empty vector
        return emptyEntityVec;
    }
}

const std::map<std::string, EntityVec> &EntityManager::getEntityMap()
{
    return m_entityMap;
}
