#ifndef _UAB_P_PLAYER_H_
#define _UAB_P_PLAYER_H_

#include <vector>

#include "entity/component.h"
#include "process.h"

class PPlayer : public UpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PPlayer() {}
    ~PPlayer() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
};


#endif