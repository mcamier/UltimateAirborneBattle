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
    initGame();

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

    if (!isMatchDone()) {
        // check if entities are out of world borders
        for (std::vector<entityID>::iterator it = m_gameWorldEntities.begin()
            ; it != m_gameWorldEntities.end()
            ; it++) {
            CTransform *pos = getScene().getEntityManager().getAs<CTransform>((*it));
            if (pos != NULL) {
                // if too far out of screen, remove the entity
                if (pos->m_position.getX() > 1500 ||
                    pos->m_position.getX() < -1500 ||
                    pos->m_position.getY() > 1000 ||
                    pos->m_position.getY() < -1000) {

                    printf("entity %d out of bounds then remove it\n", (*it));
                    getScene().getEntityManager().removeEntity((*it));
                }
            }
        }

        // Bomb spawning
        /*
        if (m_bombTiming > 5000) {
            m_bombTiming = 0;
            int x = MathUtils::randint(1280);
            ActorFactory::get()->createBomb(getScene().getEntityManager(), x);
        }
        else {
            m_bombTiming += gameTime.getElapsedMillisecond();
        }*/
    }
    else if(isMatchDone() && !m_gameDone) {    
        printf("The game is done\n");
        m_gameDone = true;
        EventManager::get()->queueEvent(new GameWonEvent());
    }
}

void PGameManager::initGame() {
    ActorFactory::get()->createBackground(getScene().getEntityManager());
    switch (m_gameMode) {
    case ONE_VS_ONE:
        initOneVsOne();
        break;
    case TWO_VS_TWO:
        initTwoVsTwo();
        break;
    case FFA_THEE_PLAYERS:
        initThreePlayersFFA();
        break;
    case FFA_FOUR_PLAYERS:
        initFourPlayersFFA();
        break;
    }
}

void PGameManager::initOneVsOne() {
    m_playerOne = ActorFactory::get()->createPlayerOne(getScene().getEntityManager(), 320, 360);
    m_playerTwo = ActorFactory::get()->createPlayerTwo(getScene().getEntityManager(), 960, 360);
    m_playerThree = -1;
    m_playerFour = -1;
}
void PGameManager::initTwoVsTwo() {
    m_playerOne = ActorFactory::get()->createPlayerOne(getScene().getEntityManager(), 320, 180);
    m_playerTwo = ActorFactory::get()->createPlayerTwo(getScene().getEntityManager(), 960, 180);
    m_playerThree = ActorFactory::get()->createPlayerThree(getScene().getEntityManager(),320, 540);
    m_playerFour = ActorFactory::get()->createPlayerFour(getScene().getEntityManager(), 960, 540);
}

void PGameManager::initThreePlayersFFA() {
    m_playerOne = ActorFactory::get()->createPlayerOne(getScene().getEntityManager(), 320, 180);
    m_playerTwo = ActorFactory::get()->createPlayerTwo(getScene().getEntityManager(), 960, 180);
    m_playerThree = ActorFactory::get()->createPlayerThree(getScene().getEntityManager(), 320, 540);
    m_playerFour = -1;
}

void PGameManager::initFourPlayersFFA() {
    m_playerOne = ActorFactory::get()->createPlayerOne(getScene().getEntityManager(), 320, 180);
    m_playerTwo = ActorFactory::get()->createPlayerTwo(getScene().getEntityManager(), 960, 180);
    m_playerThree = ActorFactory::get()->createPlayerThree(getScene().getEntityManager(), 320, 540);
    m_playerFour = ActorFactory::get()->createPlayerFour(getScene().getEntityManager(), 960, 540);
}

bool PGameManager::isMatchDone() {
    int alive = 0;
    switch (m_gameMode) {
    case ONE_VS_ONE:
        return (m_bPlayerOneDead || m_bPlayerTwoDead);
        break;
    case TWO_VS_TWO:
        return (m_bPlayerOneDead && m_bPlayerTwoDead) || (m_bPlayerThreeDead && m_bPlayerFourDead);
        break;
    case FFA_THEE_PLAYERS:
        alive = (!m_bPlayerOneDead) ? alive++ : alive;
        alive = (!m_bPlayerTwoDead) ? alive++ : alive;
        alive = (!m_bPlayerThreeDead) ? alive++ : alive;
        return (alive <= 1);
        break;
    case FFA_FOUR_PLAYERS:
        alive = (!m_bPlayerOneDead) ? alive++ : alive;
        alive = (!m_bPlayerTwoDead) ? alive++ : alive;
        alive = (!m_bPlayerThreeDead) ? alive++ : alive;
        alive = (!m_bPlayerFourDead) ? alive++ : alive;
        return (alive <= 1);
        break;
    }
    return false;
}


void PGameManager::onMissileFired(IEvent *eventData) {
    MissileFiredEvent *e = static_cast<MissileFiredEvent*>(eventData);

    float angle = 0;
    if (e->m_direction.getX() != 0 || e->m_direction.getY() != 0) {
       angle = (float)atan2(e->m_direction.getX(), e->m_direction.getY()) * (180 / MathUtils::PI);
    }

    entityID id = ActorFactory::get()->createMissile(getScene().getEntityManager(), e->m_direction, e->m_sourcePosition, angle);
    m_gameWorldEntities.push_back(id);
    std::cout << "missile fired" << std::endl;
}


void PGameManager::onInputFire(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_FIRE_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;

        CPlayer* player = getScene().getEntityManager().getAs<CPlayer>(playerID);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        if (player->m_bAlive){
            if (player->m_cooldown <= 0) {
                player->m_cooldown = player->m_defaultCooldown;

                Vec2f direction;
                direction.setX(MathUtils::cosFromDeg(transform->m_rotation) * 2);
                direction.setY(MathUtils::sinFromDeg(transform->m_rotation) * 2);

                EventManager::get()->queueEvent(new MissileFiredEvent(getScene().getID(), transform->m_position, direction));
            }
        }
    }
}

void PGameManager::onInputThrust(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_THRUST_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
        CRigidBody* rigidBody = getScene().getEntityManager().getAs<CRigidBody>(playerID);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        CPlayer* player = getScene().getEntityManager().getAs<CPlayer>(playerID);

        if (player->m_bAlive){
            int x = player->m_forward.getX();
            int y = player->m_forward.getY();

            Vec2f newVelocity = Vec2f(player->m_forward);

            newVelocity.setX(x * MathUtils::cosFromDeg(transform->m_rotation) - y * MathUtils::sinFromDeg(transform->m_rotation));
            newVelocity.setY(y * MathUtils::cosFromDeg(transform->m_rotation) + x * MathUtils::sinFromDeg(transform->m_rotation));
            newVelocity *= 300.0f;

            rigidBody->m_velocity.set(newVelocity.getX(), newVelocity.getY());
        }
    }
}

void PGameManager::onInputOrientation(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_ORIENTATION_EVENT) {
        entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(playerID);
        CPlayer* player = getScene().getEntityManager().getAs<CPlayer>(playerID);

        if (player->m_bAlive){
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
           // rawY = -rawY;
            rawY = (player->m_forward.getX() > 0) ? -rawY : rawY;
            rawX = (player->m_forward.getX() > 0) ? rawX : -rawX;

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
}

void PGameManager::onExplosion(IEvent *eventData) {
    PlayerDestroyedEvent *e = static_cast<PlayerDestroyedEvent*>(eventData);

    if (e->m_player == m_playerOne) { m_bPlayerOneDead = true; }
    else if (e->m_player == m_playerTwo) { m_bPlayerTwoDead = true; }
    else if (e->m_player == m_playerThree) { m_bPlayerThreeDead = true; }
    else if (e->m_player == m_playerFour) { m_bPlayerFourDead = true; }

    if (e->m_spaceIDTarget == getScene().getID()) {
        entityID id = ActorFactory::get()->createExplosion(getScene().getEntityManager(), e->m_location);
        //CRigidBody *rb = getScene().getEntityManager().getAs<CRigidBody>(e->m_player);
        //rb->m_bApplyGravity = true;

        m_gameWorldEntities.push_back(id);
        
    }
}