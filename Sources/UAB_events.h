#ifndef _UAB_EVENTS_H
#define _UAB_EVENTS_H

#include "CPT_event.h"
#include "CPT_vec2f.h"
#include "CPT_scene.h"
#include "CPT_entityManager.h"
#include "C_collider.h"
#include "C_transform.h"


#define INPUT_PAUSE_EVENT       99

#define INPUT_FIRE_EVENT        100
#define INPUT_THRUST_EVENT      101
#define INPUT_ORIENTATION_EVENT 102



class MissileFiredEvent : public SceneAwareEvent {

public:
    entityID m_playerSource;
    Vec2f m_sourcePosition;
    Vec2f m_direction;

public:
    MissileFiredEvent(unsigned int spaceIDTarget, Vec2f& sourcePosition, Vec2f direction) :
        SceneAwareEvent(spaceIDTarget),
        m_sourcePosition(sourcePosition),
        m_direction(direction) {}

    ~MissileFiredEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "Missile_Fired"; }
};

class PlayerDestroyedEvent : public SceneAwareEvent {

public:
    entityID m_player;
    Vec2f m_location;

public:
    PlayerDestroyedEvent(unsigned int spaceIDTarget, entityID player, Vec2f location) :
        SceneAwareEvent(spaceIDTarget),
        m_player(player),
        m_location(location) {}

    ~PlayerDestroyedEvent() {}

    static const EventType sk_EventType;

    const EventType getEventType(void) const { return sk_EventType; }
    const char* getName(void) const { return "Player_Destroyed"; }
};


class ExplosionEvent : public SceneAwareEvent {

public:
    entityID m_player;
    Vec2f m_location;

public:
    ExplosionEvent(unsigned int spaceIDTarget, Vec2f location) :
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
        //scene->getEntityManager().removeComponent(thisEntity, CCollider::sk_componentType);
        Vec2f location = Vec2f(0, 0);
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