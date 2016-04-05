#ifndef _UAB_EVENTS_H
#define _UAB_EVENTS_H

#include "core/CPT_locator.h"
#include "CPT_event.h"
#include "CPT_scene.h"
#include "entity/CPT_entityManager.h"
#include "components/C_collider.h"
#include "components/C_player.h"
#include "components/C_transform.h"
#include "components/C_missile.h"

#include "glm/vec2.hpp"


#define INPUT_PAUSE_EVENT       99
#define INPUT_RESET_EVENT       98

#define INPUT_FIRE_EVENT        100
#define INPUT_THRUST_EVENT      101
#define INPUT_ORIENTATION_EVENT 102

class MissileFiredEvent : public SceneAwareEvent {

public:
    entityID m_playerSource;

public:
    MissileFiredEvent(unsigned int spaceIDTarget, entityID shooter) :
        SceneAwareEvent(spaceIDTarget),
        m_playerSource(shooter) {}

    ~MissileFiredEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "Missile_Fired"; }
};

class PlayerDestroyedEvent : public SceneAwareEvent {

public:
    entityID m_player;
    entityID m_killer;
    glm::vec2 m_location;

public:
    PlayerDestroyedEvent(unsigned int spaceIDTarget, entityID player, glm::vec2 location, entityID killer) :
        SceneAwareEvent(spaceIDTarget),
        m_player(player),
        m_killer(killer),
        m_location(location) {}

    ~PlayerDestroyedEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "Player_Destroyed"; }
};

class GameWonEvent : public BaseEvent {
public:
    GameWonEvent() {}
    ~GameWonEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "GameWon"; }
};



class ExplosionEvent : public SceneAwareEvent {

public:
    entityID m_player;
    glm::vec2 m_location;

public:
    ExplosionEvent(unsigned int spaceIDTarget, glm::vec2 location) :
        SceneAwareEvent(spaceIDTarget),
        m_location(location) {}

    ~ExplosionEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "Player_Destroyed"; }
};


class Functor {
public:
    virtual void operator()(entityID thisEntity, entityID collidesAgainst, const AbstractScene* withinScene) const = 0;
};


class PlayerCollideFunctor : public Functor {
public:
    void operator()(entityID thisEntity, entityID collidesAgainst, const AbstractScene* scene) const {
        printf("player collision reaction once\n");
        CMissile* missile = scene->getEntityManager().getAs<CMissile>(collidesAgainst);

        // when player shoot the missile will collide with shooter for a short period of time
        // so in the case we are colliding with missile from this player we are preventing
        // that missile destroy the aircraft at its begin lifetime
        if (missile != nullptr && 
            missile->m_bThrowerStillImmune && 
            missile->m_throwerID == thisEntity) {
            // in order this trick works, collision callback should be fired once for all contact duration
            missile->m_bThrowerStillImmune = false;
        }
        else {
            CPlayer *player = scene->getEntityManager().getAs<CPlayer>(thisEntity);
            if (player->m_bAlive) {
                player->m_bAlive = false;

                CTransform *t1 = scene->getEntityManager().getAs<CTransform>(thisEntity);
                glm::vec2 position = glm::vec2(t1->getX(), t1->getY());
                
                if (missile != nullptr) {
                    Locator::getEventManager()->queueEvent(new PlayerDestroyedEvent(scene->getID(), thisEntity, position, missile->m_throwerID));
                }
                else {
                    Locator::getEventManager()->queueEvent(new PlayerDestroyedEvent(scene->getID(), thisEntity, position, -1));
                }
            }

            if (missile != nullptr) {
                scene->getEntityManager().removeEntity(collidesAgainst);
            }
        }
    }
};


class DestructibeColliderFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const AbstractScene* scene) const {
        scene->getEntityManager().removeEntity(thisEntity);
    }
};



#endif