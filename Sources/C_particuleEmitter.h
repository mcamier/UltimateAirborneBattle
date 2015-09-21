#ifndef _C_PARTICULE_EMITTER_H_
#define _C_PARTICULE_EMITTER_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_graphic.h"
#include "CPT_vec2f.h"

typedef struct particule_s {
    Sprite* sprite;
    float lifetime; // as milliseconds
    float maxLifetime; // as milliseconds
    int angle;
    float x;
    float y;
    float vx;
    float vy;
} particule_t;

class CParticuleEmitter : public IComponent {
public:
    const static ComponentType sk_componentType = 0xcf69cb7d;

public:
    //                          Particules creation values
    Sprite                     *m_sprite;
    float                       m_lifetime;
    bool                        m_bIsGravityApplied;
    Vec2f                       m_forceApplied;

    //                          Emitter settings
    bool                        m_bIsEmitting;
    int                         m_particulePerSecond;
    float                       m_angle;
    float                       m_angleThreshold;
    float                       m_rate;
    float                       m_elapsedRate;
    int                         m_angleRotationPerSecond;

    CParticuleEmitter(Sprite *sprite, float lifetime, Vec2f forceApplied, int particulePerSecond, int angleRotationPerSecond) :
        m_sprite(sprite),
        m_lifetime(lifetime),
        m_forceApplied(forceApplied),
        m_particulePerSecond(particulePerSecond),
        m_bIsEmitting(true),
        m_rate(1000.0f / particulePerSecond),
        m_elapsedRate(0),
        m_angleRotationPerSecond(angleRotationPerSecond) {}

    virtual ~CParticuleEmitter() {}

    inline const ComponentType getComponentType(void) const {
        return CParticuleEmitter::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CParticuleEmitter";
    }
};


#endif