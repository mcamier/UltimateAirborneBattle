#include "P_plusOne.h"

#include "C_plusOne.h"
#include "C_transform.h"

ComponentType bb[] = { CPlusOne::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PPlusOne::sk_requirements(bb, bb + 2);

void PPlusOne::v_updateEntity(entityID id, const GameTime& gameTime) {
    CPlusOne *obj = getEntityAs<CPlusOne>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    obj->m_elapsedTime += gameTime.getElapsedMillisecond();
    float interpolation = obj->m_elapsedTime / obj->m_lifeTimeDuration;

    transform->setScaleX(interpolation);
    transform->setScaleY(interpolation);

    if (obj->m_elapsedTime >= obj->m_lifeTimeDuration) {
        getScene().getEntityManager().removeEntity(id);
    }
}