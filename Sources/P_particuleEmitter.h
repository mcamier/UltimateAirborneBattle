#ifndef _P_PARTICULE_EMITTER_H_
#define _P_PARTICULE_EMITTER_H_

#include <vector>

#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_process.h"
#include "CPT_component.h"

class PParticuleEmitter : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PParticuleEmitter() {}
    virtual ~PParticuleEmitter() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int getID() const;
    void v_process(entityID id, const GameTime& gameTime) override;
    void v_destroy() override;
};
#endif