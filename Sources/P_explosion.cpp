#include "P_explosion.h"

#include "C_explosion.h"
#include "C_collider.h"


ComponentType aa[] = { CExplosion::sk_componentType };
const std::vector<ComponentType> PExplosion::sk_requirements(aa, aa + 1);

void PExplosion::v_updateEntity(entityID id, const GameTime& gameTime) {
    CExplosion *explosion = getEntityAs<CExplosion>(id);
    //CCollider *collider = getEntityAs<CCollider>(id);
   
    explosion->m_elapsedLifetime += gameTime.getElapsedMillisecond();
    
    if (explosion->m_elapsedLifetime >= explosion->m_endCollideAt) {
        //collider->m_bActivated = false;
        // the explosion lifetime is over, then kill it
        if (explosion->m_elapsedLifetime >= explosion->m_lifetime) { 
            getScene().getEntityManager().removeEntity(id);
        }
    } else {
        //collider->m_bActivated = true;
    }
}