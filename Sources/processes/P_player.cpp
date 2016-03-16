#include "processes/P_player.h"
#include "SDL2/SDL.h"

#include "components/C_player.h"
#include "components/C_transform.h"
#include "UAB_events.h"

#include "CPT_math.h"
#include "UAB_defines.h"
#include "CPT_locator.h"


ComponentType h[] = { CPlayer::sk_componentType, CTransform::sk_componentType, CRigidBody::sk_componentType };
const std::vector<ComponentType> PPlayer::sk_requirements(h, h +3);

void PPlayer::v_updateEntity(entityID id, const GameTime& gameTime) {
    CPlayer *player = getEntityAs<CPlayer>(id);
    CTransform *transform = getEntityAs<CTransform>(id);
    CRigidBody *body = getEntityAs<CRigidBody>(id);

    if (player->m_bAlive) {
        player->m_elapsedTime += gameTime.getElapsedMillisecond();
        double temp = 0.25f * sin((double)(MathUtils::TWO_PI * 0.001 * player->m_elapsedTime + 0));

        // set screen position with floating in account
        player->m_floatingAmount = temp;
        transform->setOffsetY(transform->getOffsetY() + player->m_floatingAmount);

        if (player->m_bSpeedUp) {
            if (player->m_actualThrustAmount < player->m_speedupThrustAmount) {
                player->m_actualThrustAmount += 350 * gameTime.getElapsedSecond();
            }
            player->m_bSpeedUp = false;
        }
        else {
            if (player->m_actualThrustAmount < player->m_maxThrustAmount) {
                player->m_actualThrustAmount += 150 * gameTime.getElapsedSecond();
            }
            else if (player->m_actualThrustAmount > player->m_maxThrustAmount) {
                player->m_actualThrustAmount -= 250 * gameTime.getElapsedSecond();
            }
        }
        
        body->m_velocity.y = sin(transform->getRotation()) * player->m_actualThrustAmount;
        body->m_velocity.x = player->m_forward.x * cos(transform->getRotation()) * player->m_actualThrustAmount;

        if (player->m_cooldown > 0) {
            player->m_cooldown -= gameTime.getElapsedMillisecond();
            // Design issue : Draw with UpdateProcess
            Locator::getRenderer()->renderRectangle(true, transform->getX() - 25, transform->getY() + 55, 75, 5, 0xFF, 0xFF, 0xFF);
            Locator::getRenderer()->renderRectangle(true, transform->getX() - 25, transform->getY() + 55, (1 - (player->m_cooldown / player->m_defaultCooldown)) * 75, 5, 0x66, 0x99, 0x99);
        }
    }
}