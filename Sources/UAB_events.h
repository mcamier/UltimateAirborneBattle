#ifndef _UAB_EVENTS_H
#define _UAB_EVENTS_H

#include "CPT_event.h"
#include "CPT_vec2f.h"
#include "CPT_scene.h"
#include "CPT_entityManager.h"
#include "C_collider.h"

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
    }
};


class BombCollideFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
        printf("bomb collision reaction\n");
        scene->getEntityManager().removeComponent(thisEntity, CCollider::sk_componentType);
    }
};


class MissileCollideFunctor : public Functor {
    void operator()(entityID thisEntity, entityID collidesAgainst, const Scene* scene) const {
        printf("Missile collision reaction\n");
        scene->getEntityManager().removeComponent(thisEntity, CCollider::sk_componentType);
    }
};


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

#endif