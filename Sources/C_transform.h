#ifndef _C_TRANSFORM_H
#define _C_TRANSFORM_H

#include "CPT_component.h"
#include "CPT_vec2f.h"

class CTransform : public IComponent {
public:
    const static ComponentType sk_componentType = 0x381cfbe0;

    Vec2f m_position;
    float m_rotation;
    Vec2f m_scale;

    CTransform() : 
        m_position(Vec2f()), 
        m_rotation(0), 
        m_scale(Vec2f(1, 1)) {}

    CTransform(int x, int y) :
        m_rotation(0),
        m_scale(Vec2f(1, 1)),
        m_position(Vec2f(x, y)){}

    CTransform(int x, int y, int rotation) :
        m_rotation(rotation),
        m_scale(Vec2f(1, 1)),
        m_position(Vec2f(x, y)){}

    CTransform(int x, int y, int rotation, Vec2f scale) :
        m_rotation(rotation),
        m_position(Vec2f(x, y)),
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