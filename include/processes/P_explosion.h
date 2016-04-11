#ifndef _UAB_P_EXPLOSION_H_
#define _UAB_P_EXPLOSION_H_

#include <vector>

#include "entity/CPT_component.h"
#include "process.h"

class PExplosion : public UpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PExplosion() {}
    ~PExplosion() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
};


#endif