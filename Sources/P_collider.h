#ifndef _P_COLLIDER_H_
#define _P_COLLIDER_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"
#include "CPT_memory.h"

typedef struct collision_s {
    entityID    obj1;
    entityID    obj2;
    float       penetrationDistance;
} collision_t;

class PCollider : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

    DoubleBufferedStackAllocator            *m_lastFrameCollisions;

public:
    PCollider() : m_lastFrameCollisions(new DoubleBufferedStackAllocator(sizeof(collision_s) * 100)) {}
    ~PCollider() {}

    inline const unsigned int getID() const { return 10012; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_initialize(void);
    void v_destroy(void);

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
};
#endif