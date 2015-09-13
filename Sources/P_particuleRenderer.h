#ifndef _P_PARTICULE_RENDERER_H_
#define _P_PARTICULE_RENDERER_H_

#include <vector>

#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_process.h"
#include "CPT_component.h"

class PParticuleRenderer : public EntityRenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PParticuleRenderer() {}
    virtual ~PParticuleRenderer() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int getID() const;
    void v_processRender(entityID id, const GameTime& gameTime) override;
    void v_destroy() override;
};
#endif