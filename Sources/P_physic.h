#ifndef _P_PHYSICS2D_H_
#define _P_PHYSICS2D_H_

#include "CPT_process.h"

#include "C_rigidbody.h"

class PPhysics2D : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PPhysics2D() {};

    const unsigned int getID() const { return 10002; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
    void v_destroy(void);
};

#endif