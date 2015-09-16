#include "P_screenPosition.h"

#include "C_transform.h"


ComponentType z[] = { CTransform::sk_componentType };
const std::vector<ComponentType> PScreenPosition::sk_requirements(z, z + 1);

void PScreenPosition::v_process(entityID id, const GameTime& gameTime) {
    CTransform *pos = getEntityAs<CTransform>(id);

    // if too far out of screen, remove the entity
    if (pos->m_position.getX() > 2000 ||
        pos->m_position.getX() < -500 ||
        pos->m_position.getY() > 1000 ||
        pos->m_position.getY() < -500){
        
        printf("entity %d out of bounds then remove it\n", id);
        getScene().getEntityManager().removeEntity(id);

    }
}