#ifndef _TILE_PROCESS_H_
#define _TILE_PROCESS_H_

#include "process.h"
#include "core/core.h"
#include "entity/entity.h"
#include "graphic/rendererManager.h"
#include "CPT_event.h"
#include "graphic/graphic.h"

#include "components/C_transform.h"
#include "components/C_sprite.h"

using Compote::Core::GameTime;

class PSpriteRenderer : public RenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PSpriteRenderer() {}
    virtual ~PSpriteRenderer() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void v_processRender(entityID id, const GameTime& gameTime);
    void v_destroy();
};

#endif