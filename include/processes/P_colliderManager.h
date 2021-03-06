#ifndef P_COLLIDER_MANAGER_H_
#define P_COLLIDER_MANAGER_H_

#include <vector>

#include "core/core.h"
#include "entity/entity.h"
#include "process.h"
#include "entity/component.h"
#include "memory/doubleBufferedStackAllocator.h"
#include "entity/components/C_particuleEmitter.h"

#include "collisions_utils.h"

using Compote::Core::GameTime;
using Compote::Memory::DoubleBufferedStackAllocator;

class PColliderManager : public UpdateProcess {

private:
    static const std::vector<ComponentType> sk_requirements;

    DoubleBufferedStackAllocator            *m_pDetectedCollisions;
    collision_s                             *m_pHeadCurrentCollisions;
    collision_s                             *m_pHeadOldCollisions;

public:
    PColliderManager() : 
        m_pDetectedCollisions(new DoubleBufferedStackAllocator(sizeof(collision_s) * 100)) {}
    ~PColliderManager() {}

    const std::vector<ComponentType> getRequirements    () const {
        return sk_requirements;
    }

    bool                    v_initialize                (void);
    void                    v_destroy                   (void);

private:
    void                    v_before                    (const GameTime& gameTime);
    void                    v_updateEntity              (entityID id, const GameTime& gameTime) {};
    bool                    collisionOccuredLastFrame   (entityID id1, entityID id2);
    void                    addCollision                (entityID id1, entityID id2);
};
#endif