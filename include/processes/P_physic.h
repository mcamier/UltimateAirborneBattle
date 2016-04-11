#ifndef _P_PHYSICS2D_H_
#define _P_PHYSICS2D_H_

#include "process.h"

#include "components/C_rigidbody.h"

class PPhysics2D : public UpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PPhysics2D() {};

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
    void v_destroy(void);
};

#endif