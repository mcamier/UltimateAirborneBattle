#ifndef _UAB_EVENTS_H
#define _UAB_EVENTS_H

#include "CPT_event.h"
#include "CPT_scene.h"
#include "CPT_entityManager.h"
#include "C_collider.h"
#include "C_player.h"
#include "C_transform.h"

#include "vec2.hpp"


#define INPUT_PAUSE_EVENT       99

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
    glm::vec2 m_location;

public:
    PlayerDestroyedEvent(unsigned int spaceIDTarget, entityID player, glm::vec2 location) :
        SceneAwareEvent(spaceIDTarget),
        m_player(player),
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
    virtual void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* withinScene) const = 0;
};


class PlayerCollideFunctor : public Functor {
public:
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
        printf("player collision reaction\n");
        // what about deactivate it instead of removing
        scene->getEntityManager().removeComponent(thisEntity, CCollider::sk_componentType);
        glm::vec2 location = glm::vec2(.0f, .0f);
        CPlayer *player = scene->getEntityManager().getAs<CPlayer>(thisEntity);
        player->m_bAlive = false;

        CTransform *t1 = scene->getEntityManager().getAs<CTransform>(thisEntity);
        CTransform *t2 = scene->getEntityManager().getAs<CTransform>(collidesAgainst);

        //location = (t1->m_position - t2->m_position) + t1->m_position;

        EventManager::get()->queueEvent(new PlayerDestroyedEvent(scene->getID(), thisEntity, t1->m_position));
    }
};


class BombCollideFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
        scene->getEntityManager().removeEntity(thisEntity);
        CTransform *t1 = scene->getEntityManager().getAs<CTransform>(thisEntity);
        EventManager::get()->queueEvent(new ExplosionEvent(scene->getID(), t1->m_position));
    }
};


class MissileCollideFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
        scene->getEntityManager().removeEntity(thisEntity);
        CTransform *t1 = scene->getEntityManager().getAs<CTransform>(thisEntity);
        EventManager::get()->queueEvent(new ExplosionEvent(scene->getID(), t1->m_position));
    }
};

class ExplosionCollideFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
    
    }
};



#endif