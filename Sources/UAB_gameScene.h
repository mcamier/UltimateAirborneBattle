#ifndef _UAB_GAME_SCENE_H_
#define _UAB_GAME_SCENE_H_

#include <assert.h>
#include "CPT_scene.h"

#include "UAB_defines.h"
#include "P_physic.h"
#include "P_player.h"
#include "P_rendereable2D.h"
#include "P_particuleManager.h"
#include "P_animation.h"
#include "P_explosion.h"
#include "P_colliderManager.h"
#include "P_plusOne.h"
#include "CPT_math.h"

using namespace std;

class GameConstant {
public:
    static const int X_LIMIT = 2000;
    static const int Y_LIMIT = 2000;
    static const int BOMB_SPAWN_RATE = 10000;
};

enum GameMode {
    ONE_VS_ONE,
    TWO_VS_TWO,
    FFA_THEE_PLAYERS,
    FFA_FOUR_PLAYERS
};

class UABGameScene : public Scene {

public:
    UABGameScene() : 
        Scene("GAME screen", false, true, "../Resources/inputs/inputs_game.xml") {}

    const unsigned int  getID() const { return 10005; }


private:
    GameMode            m_gameMode = GameMode::TWO_VS_TWO;
    bool                m_gameDone = false;

    bool                m_bPlayerOneDead = false;
    bool                m_bPlayerTwoDead = false;
    bool                m_bPlayerThreeDead = false;
    bool                m_bPlayerFourDead = false;

    entityID            m_playerOne = -1;
    entityID            m_playerTwo = -1;
    entityID            m_playerThree = -1;
    entityID            m_playerFour = -1;

    float               m_bombTiming = 0;

    Delegate<IEvent*>   d_missileFired;
    Delegate<IEvent*>   d_explosionOccurs;
    Delegate<IEvent*>   d_playerDestroyed;
    Delegate<IEvent*>   d_inputFire;
    Delegate<IEvent*>   d_inputThrust;
    Delegate<IEvent*>   d_inputOrientation;

    list<entityID>      m_gameWorldEntities;

protected:
    void initialize(void) {
        assert(ActorFactory::get() != NULL);

        this->addProcess(new PColliderManager());
        //this->addProcess(new PCollider());
        this->addProcess(new PAnimation());
        this->addProcess(new PPlayer());
        this->addProcess(new PExplosion());
        this->addProcess(new PPhysics2D());
        this->addProcess(new PParticuleManager()); 
        this->addProcess(new PPlusOne());

        this->addRenderProcess(new PRendereable2D());
    
        d_missileFired = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onMissileFired>(this);
        EventManager::get()->addListener(MissileFiredEvent::sk_EventType, d_missileFired);
        d_inputFire = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputFire>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputFire);
        d_inputThrust = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputThrust>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputThrust);
        d_inputOrientation = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputOrientation>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputOrientation);
        d_playerDestroyed = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onExplosion>(this);
        EventManager::get()->addListener(PlayerDestroyedEvent::sk_EventType, d_playerDestroyed);
        d_explosionOccurs = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onExplosion>(this);
        EventManager::get()->addListener(ExplosionEvent::sk_EventType, d_explosionOccurs);

        initGame();
    }

    void  v_update(const GameTime& gameTime) {
        Scene::v_update(gameTime);

        if (!isMatchDone()) {
            // check if entities are out of world borders
            for (list<entityID>::iterator it = m_gameWorldEntities.begin()
                ; it != m_gameWorldEntities.end() ;) {
                CTransform *pos = getEntityManager().getAs<CTransform>((*it));
                if (pos != NULL) {
                    // if too far out of screen, remove the entity
                    if (pos->getX() > GameConstant::X_LIMIT ||
                        pos->getX() < -GameConstant::X_LIMIT ||
                        pos->getY() > GameConstant::Y_LIMIT ||
                        pos->getY() < -GameConstant::Y_LIMIT) {

                        printf("entity [%d] out of bounds then remove it\n", (*it));
                        getEntityManager().removeEntity((*it));
                        m_gameWorldEntities.erase(it++);
                    } else { ++it; }
                } else { ++it; }
            }

            // Bomb spawning
            if (m_bombTiming > GameConstant::BOMB_SPAWN_RATE) {
                m_bombTiming = 0;
                entityID bomb = ActorFactory::get()->createBomb(getEntityManager(), MathUtils::randint(1280));
                m_gameWorldEntities.push_back(bomb);
            }
            else {
                m_bombTiming += gameTime.getElapsedMillisecond();
            }
        }
        else if (isMatchDone() && !m_gameDone) {
            printf("The game is done\n");
            m_gameDone = true;
            EventManager::get()->queueEvent(new GameWonEvent());
        }
    }

private:
    void initGame() {
        ActorFactory::get()->createBackground(getEntityManager());
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

    void initOneVsOne() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 320, 360);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 960, 360);
        m_playerThree = -1;
        m_playerFour = -1;
    }
    void initTwoVsTwo() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 320, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 960, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 320, 540);
        m_playerFour = ActorFactory::get()->createPlayerFour(getEntityManager(), 960, 540);
    }

    void initThreePlayersFFA() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 320, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 960, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 320, 540);
        m_playerFour = -1;
    }

    void initFourPlayersFFA() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 320, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 960, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 320, 540);
        m_playerFour = ActorFactory::get()->createPlayerFour(getEntityManager(), 960, 540);
    }

    bool isMatchDone() {
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


    void onMissileFired(IEvent *eventData) {
        MissileFiredEvent *e = static_cast<MissileFiredEvent*>(eventData);

        CTransform *transform = getEntityManager().getAs<CTransform>(e->m_playerSource);
        
        glm::vec2 direction;
        direction.x = cos(transform->getRotation()) * 2;
        direction.y = sin(transform->getRotation()) * 2;

        float angle = 0;
        if (direction.x != 0 || direction.y != 0) {
            angle = (float)atan2(direction.x, direction.y) * (180 / MathUtils::PI);
        }

        glm::vec2 position = glm::vec2(transform->getX(), transform->getY());
        entityID id = ActorFactory::get()->createMissile(e->m_playerSource, getEntityManager(), direction, position, angle);
        m_gameWorldEntities.push_back(id);
    }


    void onInputFire(IEvent *eventData) {
        InputEvent *e = static_cast<InputEvent*>(eventData);

        if (e->m_spaceIDTarget == getID() && e->m_eventID == INPUT_FIRE_EVENT) {
            entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
            CPlayer* player = getEntityManager().getAs<CPlayer>(playerID);
            if (player->m_bAlive){
                if (player->m_cooldown <= 0) {
                    player->m_cooldown = player->m_defaultCooldown;
                    EventManager::get()->queueEvent(new MissileFiredEvent(getID(), playerID));
                }
            }
        }
    }


    void onInputThrust(IEvent *eventData) {
        InputEvent *e = static_cast<InputEvent*>(eventData);

        if (e->m_spaceIDTarget == getID() && e->m_eventID == INPUT_THRUST_EVENT) {
            entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
            CRigidBody* rigidBody = getEntityManager().getAs<CRigidBody>(playerID);
            CTransform* transform = getEntityManager().getAs<CTransform>(playerID);
            CPlayer* player = getEntityManager().getAs<CPlayer>(playerID);

            if (rigidBody == nullptr || 
                transform == nullptr ||
                player == nullptr){}
            else{
                if (player->m_bAlive){
                    int x = player->m_forward.x;
                    int y = player->m_forward.y;

                    glm::vec2 newVelocity = glm::vec2(player->m_forward);

                    newVelocity.x = x * cos(transform->getRotation()) - y * sin(transform->getRotation());
                    newVelocity.y = y * cos(transform->getRotation()) + x * sin(transform->getRotation());
                    newVelocity *= 300.0f;

                    rigidBody->m_velocity.x = newVelocity.x;
                    rigidBody->m_velocity.y = newVelocity.y;
                }
            }
        }
    }

    void onInputOrientation(IEvent *eventData) {
        InputEvent *e = static_cast<InputEvent*>(eventData);

        if (e->m_spaceIDTarget == getID() && e->m_eventID == INPUT_ORIENTATION_EVENT) {
            entityID playerID = (e->m_inputPayload.m_controllerIndex == 0) ? m_playerOne : m_playerTwo;
            CTransform* transform = getEntityManager().getAs<CTransform>(playerID);
            CPlayer* player = getEntityManager().getAs<CPlayer>(playerID);
            CRigidBody* rigidBody = getEntityManager().getAs<CRigidBody>(playerID);

            if (player->m_bAlive){
                float floatX, floatY;
                float rawX, rawY;
                
                rawX = e->m_inputPayload.m_range2D.x;
                rawY = e->m_inputPayload.m_range2D.y;
                
                if (rawX >= DEAD_ZONE_STICK || rawX <= -DEAD_ZONE_STICK) {
                    rawX = (rawX > 0) ? rawX - DEAD_ZONE_STICK : rawX + DEAD_ZONE_STICK;
                }
                else { rawX = 0; }

                if (rawY >= DEAD_ZONE_STICK || rawY <= -DEAD_ZONE_STICK) {
                    rawY = (rawY > 0) ? rawY - DEAD_ZONE_STICK : rawY + DEAD_ZONE_STICK;
                }
                else { rawY = 0; }

                rawY = (player->m_forward.y > 0) ? -rawY : rawY;
                rawX = (player->m_forward.x > 0) ? rawX : -rawX;

                floatX = (rawX != 0) ? rawX / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;
                floatY = (rawY != 0) ? rawY / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;
                
                float angle = 0;
                if (floatX != 0 || floatY != 0) {
                    angle = atan2(floatX, -floatY);
                }
                angle -= MathUtils::PI/2;

                transform->setRotation(angle);

            }
        }
    }

    void onExplosion(IEvent *eventData) {
        PlayerDestroyedEvent *e = static_cast<PlayerDestroyedEvent*>(eventData);
        
        if (e->m_player == m_playerOne) { m_bPlayerOneDead = true; }
        else if (e->m_player == m_playerTwo) { m_bPlayerTwoDead = true; }
        else if (e->m_player == m_playerThree) { m_bPlayerThreeDead = true; }
        else if (e->m_player == m_playerFour) { m_bPlayerFourDead = true; }

        if (e->m_spaceIDTarget == getID()) {
            entityID id = ActorFactory::get()->createExplosion(getEntityManager(), e->m_location);
            m_gameWorldEntities.push_back(id);

            if (e->m_killer >= 0) {
                CTransform *transform = getEntityManager().getAs<CTransform>(e->m_killer);
                if (transform != nullptr) {
                    id = ActorFactory::get()->createPlusOne(getEntityManager(), transform);
                    m_gameWorldEntities.push_back(id);
                }
            }

            CRigidBody *rb = getEntityManager().getAs<CRigidBody>(e->m_player);
            rb->m_bApplyGravity = true;

            
        }
    }
};

#endif