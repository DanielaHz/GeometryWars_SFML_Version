#pragma once

#include "Components.h"

#include <memory>
#include <string>

class Entity
{
public:
    friend class EntityManager;

    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";

    Entity(const size_t id, const std::string &tag);

    // Component's pointers.
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan<int>> cintLifespan;
    std::shared_ptr<CLifespan<float>> cfloatLifespan;

    std::shared_ptr<CGeneratedData> cGeneratedData;

    // Member access functions or methods declarations.
    bool isActive() const;
    const std::string &tag() const;
    const size_t id() const;
    void destroy();
};
