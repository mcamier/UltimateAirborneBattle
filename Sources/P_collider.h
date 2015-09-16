#ifndef _P_COLLIDER_H_
#define _P_COLLIDER_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"

class PCollider : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PCollider() {}
    ~PCollider() {}

    inline const unsigned int getID() const { return 10012; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_process(entityID id, const GameTime& gameTime);
};
#endif