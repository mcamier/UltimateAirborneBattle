#ifndef _P_SCREEN_POSITION_H_
#define _P_SCREEN_POSITION_H_

#include <vector>

#include "entity/CPT_component.h"
#include "process.h"

class PScreenPosition : public UpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PScreenPosition() {}
    ~PScreenPosition() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_process(entityID id, const GameTime& gameTime);
};


#endif