#ifndef _UAB_P_EXPLOSION_H_
#define _UAB_P_EXPLOSION_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"

class PExplosion : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PExplosion() {}
    ~PExplosion() {}

    inline const unsigned int getID() const { return 100015; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_process(entityID id, const GameTime& gameTime);
};


#endif