#ifndef _UAB_P_PLUSONE_H_
#define _UAB_P_PLUSONE_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"

class PPlusOne : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PPlusOne() {}
    ~PPlusOne() {}

    inline const unsigned int getID() const { return 100018; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
};


#endif