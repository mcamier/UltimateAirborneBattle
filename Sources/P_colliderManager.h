#ifndef P_COLLIDER_MANAGER_H_
#define P_COLLIDER_MANAGER_H_

#include <vector>

#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_process.h"
#include "CPT_component.h"
#include "CPT_memory.h"
#include "C_particuleEmitter.h"

#include "collisions_utils.h"

class PColliderManager : public EntityUpdateProcess {

private:
    static const std::vector<ComponentType> sk_requirements;

    DoubleBufferedStackAllocator            *m_pDetectedCollisions;
    collision_s                             *m_pHeadCurrentCollisions;
    collision_s                             *m_pHeadOldCollisions;

public:
    PColliderManager() : 
        m_pDetectedCollisions(new DoubleBufferedStackAllocator(sizeof(collision_s) * 100)) {}
    ~PColliderManager() {}

    const unsigned int      getID                       () const { return 10012; }

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