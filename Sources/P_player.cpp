#include "P_player.h"

#include "C_player.h"
#include "C_transform.h"
#include "C_screenPosition.h"


#define TWO_PI 6.2831

ComponentType h[] = { CScreenPosition::sk_componentType, CPlayer::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PPlayer::sk_requirements(h, h + 3);

void PPlayer::v_process(entityID id, const GameTime& gameTime) {
    CPlayer *player = getEntityAs<CPlayer>(id);
    CScreenPosition *screenPos = getEntityAs<CScreenPosition>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    m_elapsedTime += gameTime.getElapsedMillisecond();
    double temp = 2 * sin((double)(TWO_PI * 0.0025 * m_elapsedTime + 0));

    player->m_floatingAmount = temp;
    screenPos->m_pData->setY(transform->m_position.getY() + player->m_floatingAmount);
    screenPos->m_pData->setX(transform->m_position.getX());
}