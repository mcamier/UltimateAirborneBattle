#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include "glm/vec2.hpp"
#include "CPT_component.h"

class CPlayer : public IComponent {
public:
    const static ComponentType sk_componentType;

public:
    glm::vec2           m_forward;

    float               m_actualThrustAmount = 0.0f;
    float               m_maxThrustAmount = 300.0f;
    float               m_speedupThrustAmount = 450.0f;

    float               m_elapsedTime = 0;
    float               m_floatingAmount;
    const float         m_defaultCooldown = 1500.0f;
    float               m_cooldown = 0.0f;
    bool                m_bAlive;
    bool                m_bSpeedUp;
    

    CPlayer() : 
        m_floatingAmount(0), 
        m_forward(glm::vec2(1.0f, .0f)),
        m_bAlive(true),
        m_bSpeedUp(false) {}

    CPlayer(glm::vec2 forward) :
        m_floatingAmount(0), 
        m_forward(forward), 
        m_bAlive(true),
        m_bSpeedUp(false) {}

    virtual ~CPlayer() {}

    inline const ComponentType getComponentType(void) const {
        return CPlayer::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CPlayer";
    }
};

#endif