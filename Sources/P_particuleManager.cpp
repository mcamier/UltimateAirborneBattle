#include "P_particuleManager.h"

#include <math.h>
#include <iostream>

#include "UAB_math.h"
#include "C_particuleEmitter.h"
#include "C_transform.h"


ComponentType p[] = { CTransform::sk_componentType, CParticuleEmitter::sk_componentType };
const std::vector<ComponentType> PParticuleManager::sk_requirements(p, p + 2);


const unsigned int PParticuleManager::getID() const {
    return 10010; 
}

void PParticuleManager::v_before(const GameTime& gameTime) {
    for (std::vector<particule_t>::iterator it = m_particulesEmitted.begin()
        ; it != m_particulesEmitted.end()
        ; ++it) {

        particule_t *p = &(*it);
        p->lifetime -= gameTime.getElapsedMillisecond();

        if (p->lifetime <= 0) {
            it = m_particulesEmitted.erase(it);
        }
        else {
            // compute new particule's position according elapsed time and velocity
            p->x += p->vx * gameTime.getElapsedSecond();
            p->y += p->vy * gameTime.getElapsedSecond();

            if (p->gravityApplied){
                p->vx += 0;
                p->vy += 5.0f;
            }

            // compute new particule's velocity according elapsed time and applied force
            // TODO
            //p->vx += (float)(e->m_forceApplied.getX() * gameTime.getElapsedSecond());
            //p->vy += (float)(e->m_forceApplied.getY() * gameTime.getElapsedSecond());


        }
    }
}

void PParticuleManager::v_process(entityID id, const GameTime& gameTime) {
    CParticuleEmitter *e = getEntityAs<CParticuleEmitter>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    if (e->m_bActive) {
        e->m_elapsedRate += gameTime.getElapsedMillisecond();
        if (e->m_elapsedRate > e->m_rate)  {
            particule_t p;
            //position
            p.x = transform->m_position.getX();
            p.y = transform->m_position.getY();
            p.vx = 0;
            p.vy = 0;
            // lifetime
            p.lifetime = e->m_lifetime;
            p.maxLifetime = e->m_lifetime;
            
            p.sprite = e->m_sprite;
            p.angle = MathUtils::randint(360);
            p.gravityApplied = e->m_bIsGravityApplied;

            m_particulesEmitted.push_back(p);

            e->m_elapsedRate = 0;
        }
    }
}

void PParticuleManager::v_after(const GameTime& gameTime) {
    for (auto& particule : m_particulesEmitted) {
        SDL_Rect dest;
        dest.x = particule.x - particule.sprite->getWidth() / 2;
        dest.y = particule.y - particule.sprite->getHeight() / 2;
        dest.w = particule.sprite->getWidth();
        dest.h = particule.sprite->getHeight();

        RendererManager::get()->renderSprite(
            particule.sprite,
            &dest,
            particule.angle,
            particule.lifetime / particule.maxLifetime,
            1);

    }
}

void PParticuleManager::v_destroy() {}