#ifndef _C_TRANSFORM_H
#define _C_TRANSFORM_H

#include "CPT_component.h"

#include "vec2.hpp"

class CTransform : public IComponent {
public:
    const static ComponentType sk_componentType = 0x381cfbe0;

    glm::vec2 m_position;
    float m_rotation;
    glm::vec2 m_scale;

    CTransform() : 
        m_position(glm::vec2()),
        m_rotation(0), 
        m_scale(glm::vec2(1, 1)) {}

    CTransform(int x, int y) :
        m_rotation(0),
        m_scale(glm::vec2(1, 1)),
        m_position(glm::vec2(x, y)){}

    CTransform(int x, int y, int rotation) :
        m_rotation(rotation),
        m_scale(glm::vec2(1, 1)),
        m_position(glm::vec2(x, y)){}

    CTransform(int x, int y, int rotation, glm::vec2 scale) :
        m_rotation(rotation),
        m_position(glm::vec2(x, y)),
        m_scale(scale) {}

    virtual ~CTransform() {}

    inline const ComponentType getComponentType(void) const {
        return CTransform::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CTransform";
    }
};

#endif