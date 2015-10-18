#ifndef _C_PARTICULE_EMITTER_H_
#define _C_PARTICULE_EMITTER_H_

#include <vector>
#include "vec2.hpp"
#include "CPT_component.h"
#include "CPT_graphic.h"

typedef struct particule_s {
    Sprite* sprite;
    float lifetime; // as milliseconds
    float maxLifetime; // as milliseconds
    int angle;
    float x;
    float y;
    float vx;
    float vy;
    bool gravityApplied;
} particule_t;

class CParticuleEmitter : public IComponent {
    friend class PParticuleManager;
public:
    const static ComponentType sk_componentType = 0xcf69cb7d;

public:
    //                          Particules creation values
    Sprite                     *m_sprite;
    bool                        m_bActive;
    int                         m_particulePerSecond;

    bool                        m_bIsGravityApplied;

    float                       m_lifetime;
    float                       m_lifetimeVariation;

    float                       m_angle;
    float                       m_angleVariation;
    
    float                       m_speedVariation;
    float                       m_speed;

private:
    float                       m_rate;
    float                       m_elapsedRate;
public:
    
    CParticuleEmitter(Sprite *sprite, int particulePerSecond, float lifetime, float angle, float speed, bool gravityApplied) :
        m_sprite(sprite),
        m_lifetime(lifetime),
        m_angle(angle),
        m_speed(speed),
        m_particulePerSecond(particulePerSecond),
        m_bActive(true),
        m_rate(1000.0f / particulePerSecond),
        m_elapsedRate(0), 
        m_bIsGravityApplied(gravityApplied) {}

    virtual ~CParticuleEmitter() {}

    inline const ComponentType getComponentType(void) const {
        return CParticuleEmitter::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CParticuleEmitter";
    }
};


#endif