#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include "CPT_component.h"
#include "CPT_vec2f.h"

class CPlayer : public IComponent {
public:
    const static ComponentType sk_componentType = 0xef7366f5;

public:
    bool                m_bAlive;
    float               m_floatingAmount;
    Vec2f               m_forward;

    static const int    m_defaultCooldown = 1500;
    int                 m_cooldown = 0;

    double              m_elapsedTime = 0;

    CPlayer() : 
        m_floatingAmount(0), 
        m_forward(Vec2f(1, 0)), 
        m_bAlive(true) {}

    CPlayer(Vec2f forward) : 
        m_floatingAmount(0), 
        m_forward(forward), 
        m_bAlive(true) {}

    virtual ~CPlayer() {}

    inline const ComponentType getComponentType(void) const {
        return CPlayer::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CPlayer";
    }
};

#endif