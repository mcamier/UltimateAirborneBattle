#ifndef _C_PARTICULE_EMITTER_H_
#define _C_PARTICULE_EMITTER_H_

#include <vector>
#include "glm/vec2.hpp"
#include "CPT_component.h"
#include "CPT_graphic.h"
#include "IParticule.h"

typedef struct particule_s {
    Sprite* sprite;
    float lifetime; // as milliseconds
    float maxLifetime; // as milliseconds
    //float angle;
    float x;
    float y;
    float vx;
    float vy;
    bool gravityApplied;
} particule_t;


class CParticuleEmitter : public IComponent {
    friend class PParticuleManager;
public:
    const static ComponentType sk_componentType;

public:
    IParticule                  *m_particulePrototype;
    bool                        m_bActive;
    int                         m_particulePerSecond;

    bool                        m_bIsGravityApplied;
    float                       m_lifetime;
    float                       m_lifetimeVariation;
    float                       m_angle;
    float                       m_angleVariation;
    float                       m_speedVariation;
    float                       m_speed;
    float                       m_spawnPositionVariation;
private:
    float                       m_rate;
    float                       m_elapsedRate;
public:
    
    CParticuleEmitter(IParticule *particulePrototype, int particulePerSecond, float lifetime, float angle, float speed, bool gravityApplied) :
        m_particulePrototype(particulePrototype),
        m_lifetime(lifetime),
        m_angle(angle),
        m_speed(speed),
        m_particulePerSecond(particulePerSecond),
        m_bActive(true),
        m_rate(1000.0f / particulePerSecond),
        m_elapsedRate(0),
        m_spawnPositionVariation(0.0f),
        m_bIsGravityApplied(gravityApplied) {}

    virtual ~CParticuleEmitter() {}

    inline const ComponentType getComponentType(void) const {
        return CParticuleEmitter::sk_componentType;
    }

    static const char* getName(void) {
        return "CParticuleEmitter";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};


#endif