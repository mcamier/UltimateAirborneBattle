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

    m_elapsedTime += gameTime.getElapsedMillisecond();
    double temp = 2 * sin((double)(MathUtils::TWO_PI * 0.0025 * m_elapsedTime + 0));

    // set screen position with floating in account
    player->m_floatingAmount = temp;
    screenPos->m_pData->setY(transform->m_position.getY() + player->m_floatingAmount);
    screenPos->m_pData->setX(transform->m_position.getX());

    if (player->m_cooldown > 0) {
        player->m_cooldown -= gameTime.getElapsedMillisecond();
    }

    // plane's orientation
    int rawX = 0;
    int rawY = 0;
    float floatX = 0.0f;
    float floatY = 0.0f;
    rawX = SDL_JoystickGetAxis(SystemInputHandler::get()->getJoystick(0), XBOX_AXIS_LEFT_X);
    rawY = SDL_JoystickGetAxis(SystemInputHandler::get()->getJoystick(0), XBOX_AXIS_LEFT_Y);


    if (rawX >= DEAD_ZONE_STICK || 
        rawX <= -DEAD_ZONE_STICK || 
        rawY >= DEAD_ZONE_STICK || 
        rawY <= -DEAD_ZONE_STICK) {

        if (rawX >= DEAD_ZONE_STICK || rawX <= -DEAD_ZONE_STICK) {
            rawX = (rawX > 0) ? rawX - DEAD_ZONE_STICK : rawX + DEAD_ZONE_STICK;
        } else {
            rawX = 0;
        }

        if (rawY >= DEAD_ZONE_STICK || rawY <= -DEAD_ZONE_STICK) {
            rawY = (rawY > 0) ? rawY - DEAD_ZONE_STICK : rawY + DEAD_ZONE_STICK;
        } else {
            rawY = 0;
        }
        rawY = -rawY;

        floatX = (rawX != 0) ? rawX / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;
        floatY = (rawY != 0) ? rawY / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;

        int angle = 0;
        if (floatX != 0 || floatY != 0) {
            angle = (float)atan2(floatX, floatY) * (180 / MathUtils::PI);
        }
        angle -= 90;
        if (angle < 0) angle = 360 + angle;
        
        transform->m_rotation = angle;
    }

    // firing missile event
    if (SystemInputHandler::get()->isGamepadButtonPressedOnce(0, XBOX_BUTTON_Y)) {
        if (player->m_cooldown <= 0) {
            player->m_cooldown = player->m_defaultCooldown;

            Vec2f direction;
            direction.setX(MathUtils::cosFromDeg(transform->m_rotation));
            direction.setY(MathUtils::sinFromDeg(transform->m_rotation));

            EventManager::get()->queueEvent(new MissileFiredEvent(getScene().getID(), transform->m_position, direction));
        }
    }
}