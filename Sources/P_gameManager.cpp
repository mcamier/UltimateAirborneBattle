#include "P_gameManager.h"

#include <math.h>
#include <random>
#include <assert.h>

#include <SDL.h>
#include <SDL_image.h>

#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_event.h"
#include "CPT_scene.h"
#include "CPT_rendererManager.h"
#include "CPT_vec2f.h"



#include "UAB_math.h"

#include "UAB_defines.h"


void PGameManager::v_initialize() {

    //ActorFactory::get()->createBackground(getScene().getEntityManager());
    m_playerOne = ActorFactory::get()->createPlayerOne(getScene().getEntityManager());
    m_playerTwo = ActorFactory::get()->createPlayerTwo(getScene().getEntityManager());

    d_missileFired = Delegate<IEvent*>::make<PGameManager, &PGameManager::onMissileFired>(this);
    EventManager::get()->addListener(MissileFiredEvent::sk_EventType, d_missileFired);

    d_inputFire = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputFire>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputFire);

    d_inputThrust = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputThrust>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputThrust);

    d_inputOrientation = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputOrientation>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputOrientation);
    
    d_playerDestroyed = Delegate<IEvent*>::make<PGameManager, &PGameManager::onExplosion>(this);
    EventManager::get()->addListener(PlayerDestroyedEvent::sk_EventType, d_playerDestroyed);

    d_explosionOccurs = Delegate<IEvent*>::make<PGameManager, &PGameManager::onExplosion>(this);
    EventManager::get()->addListener(ExplosionEvent::sk_EventType, d_explosionOccurs);
}

void PGameManager::v_update(const GameTime& gameTime) {

    if (m_bombTiming > 5000) {
        m_bombTiming = 0;

        int x = MathUtils::randint(1280);
        ActorFactory::get()->createBomb(getScene().getEntityManager(), x);
    }
    else {
        m_bombTiming += gameTime.getElapsedMillisecond();
    } 
}

void PGameManager::onMissileFired(IEvent *eventData) {
    MissileFiredEvent *e = static_cast<MissileFiredEvent*>(eventData);

    float angle = 0;
    if (e->m_direction.getX() != 0 || e->m_direction.getY() != 0) {
       angle = (float)atan2(e->m_direction.getX(), e->m_direction.getY()) * (180 / MathUtils::PI);
    }

    ActorFactory::get()->createMissile(getScene().getEntityManager(), e->m_direction, e->m_sourcePosition, angle);
    std::cout << "missile fired" << std::endl;
}


void PGameManager::onInputFire(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_FIRE_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;

        CPlayer* player = getScene().getEntityManager().getAs<CPlayer>(playerID);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        if (player->m_cooldown <= 0) {
            player->m_cooldown = player->m_defaultCooldown;

            Vec2f direction;
            direction.setX(MathUtils::cosFromDeg(transform->m_rotation)*2);
            direction.setY(MathUtils::sinFromDeg(transform->m_rotation)*2);

            EventManager::get()->queueEvent(new MissileFiredEvent(getScene().getID(), transform->m_position, direction));
        }
    }
}

void PGameManager::onInputThrust(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_THRUST_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
        CRigidBody* rigidBody = getScene().getEntityManager().getAs<CRigidBody>(playerID);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        
        Vec2f newVelocity = Vec2f();
        newVelocity.setX(MathUtils::cosFromDeg(transform->m_rotation)*300);
        newVelocity.setY(MathUtils::sinFromDeg(transform->m_rotation)*300);
        
        rigidBody->m_velocity.set(newVelocity.getX(), newVelocity.getY());
    }
}

void PGameManager::onInputOrientation(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_ORIENTATION_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        float floatX, floatY;
        int rawX, rawY;

        rawX = e->m_inputPayload.m_range2D.getX();
        rawY = e->m_inputPayload.m_range2D.getY();

        if (rawX >= DEAD_ZONE_STICK || rawX <= -DEAD_ZONE_STICK) {
            rawX = (rawX > 0) ? rawX - DEAD_ZONE_STICK : rawX + DEAD_ZONE_STICK;
        }
        else { rawX = 0; }

        if (rawY >= DEAD_ZONE_STICK || rawY <= -DEAD_ZONE_STICK) {
            rawY = (rawY > 0) ? rawY - DEAD_ZONE_STICK : rawY + DEAD_ZONE_STICK;
        }
        else { rawY = 0; }
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
}

void PGameManager::onExplosion(IEvent *eventData) {
    PlayerDestroyedEvent *e = static_cast<PlayerDestroyedEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID()) {
        ActorFactory::get()->createExplosion(getScene().getEntityManager(), e->m_location);
    }
}