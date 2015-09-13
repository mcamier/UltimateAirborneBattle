#include "P_transform.h"

#include "tileComponent.h"
#include "C_transform.h"

ComponentType w[] = { CScreenPosition::getComponentType(), CTransform::getComponentType() };
const std::vector<ComponentType> PTransform::sk_requirements(w, w + 2);

void PTransform::v_process(entityID id, const GameTime& gameTime) {
    CScreenPosition *screenPos = getEntityAs<CScreenPosition>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    screenPos->m_pData->setY(transform->m_position.getY());
    screenPos->m_pData->setX(transform->m_position.getX());
}