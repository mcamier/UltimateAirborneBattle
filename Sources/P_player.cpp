#include "P_player.h"

#include "CPT_systemInputHandler.h"

#include "SDL.h"

#include "C_player.h"
#include "C_transform.h"
#include "C_screenPosition.h"
#include "UAB_events.h"
#include "CPT_vec2f.h"

#include "UAB_math.h"
#include "UAB_defines.h"


ComponentType h[] = { CScreenPosition::sk_componentType, CPlayer::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PPlayer::sk_requirements(h, h + 3);

void PPlayer::v_process(entityID id, const GameTime& gameTime) {
    CPlayer *player = getEntityAs<CPlayer>(id);
    CScreenPosition *screenPos = getEntityAs<CScreenPosition>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    player->m_elapsedTime += gameTime.getElapsedMillisecond();
    double temp = 2 * sin((double)(MathUtils::TWO_PI * 0.0025 * player->m_elapsedTime + 0));

    // set screen position with floating in account
    player->m_floatingAmount = temp;
    screenPos->m_pData->setY(transform->m_position.getY() + player->m_floatingAmount);
    screenPos->m_pData->setX(transform->m_position.getX());

    if (player->m_cooldown > 0) {
        player->m_cooldown -= gameTime.getElapsedMillisecond();
    }
    
}