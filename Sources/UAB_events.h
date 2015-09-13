#ifndef _UAB_EVENTS_H
#define _UAB_EVENTS_H

#include "CPT_event.h"


class MissileFiredEvent : public SceneAwareEvent {

public:
    entityID m_playerSource;
    Vec2f m_sourcePosition;
    Vec2f m_direction;

public:
    MissileFiredEvent(unsigned int spaceIDTarget, Vec2f& sourcePosition, Vec2f& direction) : 
        BaseEvent(0.0f), 
        m_spaceIDTarget(spaceIDTarget),
        m_sourcePosition(sourcePosition),
        m_direction(direction) {}

    ~MissileFiredEvent() {}
}

#endif