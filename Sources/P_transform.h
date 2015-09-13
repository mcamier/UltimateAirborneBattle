#ifndef _UAB_P_TRANSFORM_H_
#define _UAB_P_TRANSFORM_H_

#include <vector>

#include "CPT_component.h"
#include "CPT_process.h"

class PTransform : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

    double m_elapsedTime = 0;

public:
    PTransform() {}
    ~PTransform() {}

    inline const unsigned int getID() const { return 10009; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};

private:
    void v_process(entityID id, const GameTime& gameTime);
};


#endif