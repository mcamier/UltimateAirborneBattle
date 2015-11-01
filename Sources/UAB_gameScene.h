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
#include "C_particuleEmitter.h"
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
    GameMode            m_gameMode = GameMode::ONE_VS_ONE;
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

    entityID            m_camera;
    bool                m_bCameraShaking = false;
    float               m_cameraShakingDuration = 800.0f;
    float               m_cameraShakingElapsed = 0.0f;

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
        this->addProcess(new PAnimation());
        this->addProcess(new PPlayer());
        this->addProcess(new PExplosion());
        this->addProcess(new PPhysics2D());
        this->addProcess(new PParticuleManager()); 
        this->addProcess(new PPlusOne());

        m_camera = ActorFactory::get()->createCamera(getEntityManager());
        this->addRenderProcess(new PRendereable2D(m_camera));

        d_missileFired = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onMissileFired>(this);
        EventManager::get()->addListener(MissileFiredEvent::sk_EventType, d_missileFired);
        /*d_inputFire = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputFire>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputFire);
        d_inputThrust = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputThrust>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputThrust);
        d_inputOrientation = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onInputOrientation>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_inputOrientation);*/
        d_playerDestroyed = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onExplosion>(this);
        EventManager::get()->addListener(PlayerDestroyedEvent::sk_EventType, d_playerDestroyed);
        d_explosionOccurs = Delegate<IEvent*>::make<UABGameScene, &UABGameScene::onExplosion>(this);
        EventManager::get()->addListener(ExplosionEvent::sk_EventType, d_explosionOccurs);

        initGame();
    }

    void  v_update(const GameTime& gameTime) {
        Scene::v_update(gameTime);
        // camera shaking update
        if (m_bCameraShaking) {
            m_cameraShakingElapsed += gameTime.getElapsedMillisecond();

            CTransform *camPos = getEntityManager().getAs<CTransform>(m_camera);
            double temp = 4 * sin((double)(MathUtils::TWO_PI * 0.01 * m_cameraShakingElapsed + 0));
            camPos->setY(camPos->getY() + temp);

            if (m_cameraShakingElapsed >= m_cameraShakingDuration) {
                m_bCameraShaking = false;
                m_cameraShakingElapsed = 0.0f;
                camPos->setY(0);
            }
        }

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

            // TODO check if players are out of screen

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
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 120, 360);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 1160, 360);
        m_playerThree = -1;
        m_playerFour = -1;
    }
    void initTwoVsTwo() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 120, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 1160, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 120, 540);
        m_playerFour = ActorFactory::get()->createPlayerFour(getEntityManager(), 1160, 540);
    }

    void initThreePlayersFFA() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 120, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 1160, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 120, 540);
        m_playerFour = -1;
    }

    void initFourPlayersFFA() {
        m_playerOne = ActorFactory::get()->createPlayerOne(getEntityManager(), 120, 180);
        m_playerTwo = ActorFactory::get()->createPlayerTwo(getEntityManager(), 1160, 180);
        m_playerThree = ActorFactory::get()->createPlayerThree(getEntityManager(), 120, 540);
        m_playerFour = ActorFactory::get()->createPlayerFour(getEntityManager(), 1160, 540);
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
            angle = (float)atan2(direction.y, direction.x) * (180 / MathUtils::PI);
        }

        glm::vec2 position = glm::vec2(transform->getX(), transform->getY());
        entityID id = ActorFactory::get()->createMissile(e->m_playerSource, getEntityManager(), direction, position, angle);
        m_gameWorldEntities.push_back(id);
    }


    /*void onInputFire(IEvent *eventData) {
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
            CPlayer* player = getEntityManager().getAs<CPlayer>(playerID);
            if(player->m_bAlive){
                player->m_bSpeedUp = true;
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
                // read x and y
                rawX = e->m_inputPayload.m_range2D.x;
                rawY = e->m_inputPayload.m_range2D.y;
                floatX = (rawX != 0) ? rawX / (float)(STICK_MAX_VALUE) : 0;
                floatY = (rawY != 0) ? rawY / (float)(STICK_MAX_VALUE) : 0;

                float value = (floatX != 0 || floatY != 0) ? atan2(floatY, floatX) : 0;
                value = (value < 0) ? value + MathUtils::TWO_PI : value;
                

                float oldAngle = transform->getRotation();
                float delta = value - oldAngle;

                float newValue = transform->getRotation() + delta * 0.05f;
                if (newValue < 0) {
                    newValue = MathUtils::TWO_PI;
                }
                else if(newValue > MathUtils::TWO_PI) {
                    newValue = 0;
                }
                
                transform->setRotation(newValue);
            }
        }
    }*/

    void onExplosion(IEvent *eventData) {
        PlayerDestroyedEvent *e = static_cast<PlayerDestroyedEvent*>(eventData);
        
        if (e->m_player == m_playerOne) { m_bPlayerOneDead = true; }
        else if (e->m_player == m_playerTwo) { m_bPlayerTwoDead = true; }
        else if (e->m_player == m_playerThree) { m_bPlayerThreeDead = true; }
        else if (e->m_player == m_playerFour) { m_bPlayerFourDead = true; }

        if (e->m_spaceIDTarget == getID()) {
            entityID id = ActorFactory::get()->createExplosion(getEntityManager(), e->m_location);
            m_gameWorldEntities.push_back(id);

            AnimatedParticule *particuleProto = new AnimatedParticule(ActorFactory::get()->m_darkSmoke, 300.0f);
            CParticuleEmitter *pe = new CParticuleEmitter(particuleProto, 55, 1500, -90, 40, false);
            pe->m_angleVariation = 35;
            pe->m_spawnPositionVariation = 12;
            getEntityManager().addComponent(e->m_player, pe);

            if (e->m_killer >= 0) {
                CTransform *transform = getEntityManager().getAs<CTransform>(e->m_killer);
                if (transform != nullptr) {
                    id = ActorFactory::get()->createPlusOne(getEntityManager(), transform);
                    m_gameWorldEntities.push_back(id);
                }
            }

            CRigidBody *rb = getEntityManager().getAs<CRigidBody>(e->m_player);
            rb->m_bApplyGravity = true;

            // camera shak�ng
            m_bCameraShaking = true;
            m_cameraShakingElapsed = 0.0f;
        }
    }
};

#endif