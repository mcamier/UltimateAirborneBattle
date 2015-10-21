#include "P_particuleManager.h"

#include <math.h>
#include <iostream>

#include "CPT_math.h"
#include "C_particuleEmitter.h"
#include "C_transform.h"


ComponentType p[] = { CTransform::sk_componentType, CParticuleEmitter::sk_componentType };
const std::vector<ComponentType> PParticuleManager::sk_requirements(p, p + 2);

const unsigned int PParticuleManager::getID() const {
    return 10010; 
}

void PParticuleManager::v_before(const GameTime& gameTime) {
    for (std::list<IParticule*>::iterator it = m_particulesEmitted.begin()
        ;it != m_particulesEmitted.end()
        ;) {
        IParticule *p = (*it);
        p->update(gameTime);

        if (p->isDead()) {
            m_particulesEmitted.erase(it++);
            delete p;
        }
        else{
            it++;
        }
    }
}

void PParticuleManager::v_updateEntity(entityID id, const GameTime& gameTime) {
    CParticuleEmitter *e = getEntityAs<CParticuleEmitter>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    if (e->m_bActive) {
        e->m_elapsedRate += gameTime.getElapsedMillisecond();
        if (e->m_elapsedRate > e->m_rate)  {

            IParticule* p = e->m_particulePrototype->clone();

            p->m_x = transform->getX();
            p->m_y = transform->getY();
            
            float lv = (e->m_lifetimeVariation > 0) ? MathUtils::randint(e->m_lifetimeVariation * 2) - e->m_lifetimeVariation : 0;
            float av = (e->m_angleVariation > 0) ? MathUtils::randint(e->m_angleVariation * 2) - e->m_angleVariation : 0;
            float sv = (e->m_speedVariation > 0) ? MathUtils::randint(e->m_speedVariation * 2) - e->m_speedVariation : 0;
            
            p->m_elapsed = 0;
            p->m_lifetime = e->m_lifetime + lv;
            glm::vec2 velocity = MathUtils::fromPolar(e->m_angle + av, e->m_speed + sv);
            p->m_vx = velocity.x;
            p->m_vy = velocity.y;
        
            p->m_gravityApplied = e->m_bIsGravityApplied;

            m_particulesEmitted.push_back(p);
            e->m_elapsedRate = 0;
        }
    }
}

// After method is dedicated to particules rendering
void PParticuleManager::v_after(const GameTime& gameTime) {
    for (auto& particule : m_particulesEmitted) {
        particule->draw(gameTime);
    }
}

void PParticuleManager::v_destroy() {}