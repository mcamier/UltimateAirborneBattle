#ifndef _UAB_P_PLAYER_H_
#define _UAB_P_PLAYER_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"

class PPlayer : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PPlayer() {}
    ~PPlayer() {}

    inline const unsigned int getID() const { return 10003; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
};


#endif