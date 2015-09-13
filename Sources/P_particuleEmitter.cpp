#include "P_particuleEmitter.h"

#include <math.h>
#include <iostream>

#include "UAB_math.h"
#include "C_particuleEmitter.h"
#include "C_transform.h"


ComponentType p[] = { CTransform::sk_componentType, CParticuleEmitter::sk_componentType };
const std::vector<ComponentType> PParticuleEmitter::sk_requirements(p, p + 2);


const unsigned int PParticuleEmitter::getID() const { 
    return 10010; 
}

void PParticuleEmitter::v_process(entityID id, const GameTime& gameTime) {
    CParticuleEmitter *e = getEntityAs<CParticuleEmitter>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    // update exitants particules
    for (std::vector<particule_t>::iterator it = e->m_particulesEmitted.begin()
        ; it != e->m_particulesEmitted.end()
        ; ++it) {

        particule_t *p = &(*it);
        p->lifetime -= gameTime.getElapsedMillisecond();

        if (p->lifetime <= 0) {
            it = e->m_particulesEmitted.erase(it);
        }
        else {
            // compute new particule's position according elapsed time and velocity
            p->x += p->vx * gameTime.getElapsedSecond();
            p->y += p->vy * gameTime.getElapsedSecond();

            // compute new particule's velocity according elapsed time and applied force
            p->vx += (float)(e->m_forceApplied.getX() * gameTime.getElapsedSecond());
            p->vy += (float)(e->m_forceApplied.getY() * gameTime.getElapsedSecond());

            
            p->angle += gameTime.getElapsedSecond() * e->m_angleRotationPerSecond;
        }
    }

    e->m_elapsedRate += gameTime.getElapsedMillisecond();
    if (e->m_elapsedRate > e->m_rate)  {
        particule_t p;
        p.x = transform->m_position.getX();
        p.y = transform->m_position.getY();
        p.lifetime = e->m_lifetime;
        p.sprite = e->m_sprite;
        p.vx = 0;
        p.vy = 0;
        p.angle = MathUtils::randint(360);
       
        e->m_particulesEmitted.push_back(p);

        e->m_elapsedRate = 0;
    }
}

void PParticuleEmitter::v_destroy() {}