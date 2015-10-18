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
    for (std::list<particule_t>::iterator it = m_particulesEmitted.begin()
        ;it != m_particulesEmitted.end()
        ;) {

        particule_t *p = &(*it);
        p->lifetime -= gameTime.getElapsedMillisecond();

        if (p->lifetime <= 0) {
            m_particulesEmitted.erase(it++);
        }
        else {
            // compute new particule's position according elapsed time and velocity
            p->x += p->vx * gameTime.getElapsedSecond();
            p->y += p->vy * gameTime.getElapsedSecond();

            if (p->gravityApplied){
                p->vx += 0;
                p->vy += 5.0f;
            }
            ++it;
        }
    }
}

void PParticuleManager::v_updateEntity(entityID id, const GameTime& gameTime) {
    CParticuleEmitter *e = getEntityAs<CParticuleEmitter>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    if (e->m_bActive) {
        e->m_elapsedRate += gameTime.getElapsedMillisecond();
        if (e->m_elapsedRate > e->m_rate)  {
            particule_t p;
            p.sprite = e->m_sprite;
            p.x = transform->getX();
            p.y = transform->getY();
            
            float lv = (e->m_lifetimeVariation > 0) ? MathUtils::randint(e->m_lifetimeVariation * 2) - e->m_lifetimeVariation : 0;
            float av = (e->m_angleVariation > 0) ? MathUtils::randint(e->m_angleVariation * 2) - e->m_angleVariation : 0;
            float sv = (e->m_speedVariation > 0) ? MathUtils::randint(e->m_speedVariation * 2) - e->m_speedVariation : 0;
            
            p.lifetime = e->m_lifetime + lv;
            p.maxLifetime = e->m_lifetime + lv;
            glm::vec2 velocity = MathUtils::fromPolar(e->m_angle + av, e->m_speed + sv);
            p.vx = velocity.x;
            p.vy = velocity.y;
            //printf("angle : [%f], speed : [%f] to %f;%f\n", e->m_angle, e->m_speed, velocity.x, velocity.y);

            //p.angle = MathUtils::randint(360);            
            p.gravityApplied = e->m_bIsGravityApplied;
            m_particulesEmitted.push_back(p);
            e->m_elapsedRate = 0;
        }
    }
}

// After method is dedicated to particules rendering
void PParticuleManager::v_after(const GameTime& gameTime) {
    for (auto& particule : m_particulesEmitted) {
        SDL_Rect dest;
        dest.x = particule.x - particule.sprite->getWidth() / 2;
        dest.y = particule.y - particule.sprite->getHeight() / 2;
        dest.w = particule.sprite->getWidth();
        dest.h = particule.sprite->getHeight();

        RendererManager::get()->renderTexture(
            2,
            particule.sprite->getTexture(),
            particule.sprite->getSourceRect(),
            &dest,
            0,
            SDL_RendererFlip::SDL_FLIP_NONE,
            particule.lifetime / particule.maxLifetime);
    }
}

void PParticuleManager::v_destroy() {}