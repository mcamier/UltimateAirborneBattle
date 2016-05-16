#include "processes/P_particuleManager.h"

#include "compotemath.h"
#include "entity/components/C_particuleEmitter.h"
#include "entity/components/C_transform.h"


ComponentType p[] = { CTransform::sk_componentType, CParticuleEmitter::sk_componentType };
const std::vector<ComponentType> PParticuleManager::sk_requirements(p, p + 2);

void PParticuleManager::v_before(const GameTime& gameTime) {
    for (std::list<IParticule*>::iterator it = m_particulesEmitted.begin()
        ;it != m_particulesEmitted.end()
        ;) {
        IParticule *p = (*it);
        p->update(gameTime);

        if (p->isDead()) {
            m_particulesEmitted.erase(it++); // TODO sometime create "un segment de memoire a ete endommage"
            p->removeFromPool();
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

            // due to custom memory allocation used by clone method, the pointer could 
            // be null sometimes
            IParticule* p = e->m_particulePrototype->cloneIntoPool();
            if (p != nullptr) {

                // TODO : cause a division per zero
                /*float lv = (e->m_lifetimeVariation > 0) ? MathUtils::randint(e->m_lifetimeVariation * 2) - e->m_lifetimeVariation : 0;
                float av = (e->m_angleVariation > 0) ? MathUtils::randint(e->m_angleVariation * 2) - e->m_angleVariation : 0;
                float sv = (e->m_speedVariation > 0) ? MathUtils::randint(e->m_speedVariation * 2) - e->m_speedVariation : 0;
                float pv = (e->m_spawnPositionVariation > 0) ? MathUtils::randint(e->m_spawnPositionVariation * 2) - e->m_spawnPositionVariation : 0;*/
                float lv , av, sv, pv = 0;

                p->m_x = transform->getX() + pv;
                p->m_y = transform->getY() + pv;
                p->m_elapsed = 0;
                p->m_lifetime = e->m_lifetime + lv;
                glm::vec2 velocity = MathUtils::fromPolar(e->m_angle + av, e->m_speed + sv);
                p->m_vx = velocity.x;
                p->m_vy = velocity.y;

                p->m_gravityApplied = e->m_bIsGravityApplied;

                m_particulesEmitted.push_back(p);
            }
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