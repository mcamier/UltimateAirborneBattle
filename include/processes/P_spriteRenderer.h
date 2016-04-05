#ifndef _TILE_PROCESS_H_
#define _TILE_PROCESS_H_



#include "CPT_process.h"
#include "core/CPT_time.h"
#include "entity/CPT_entity.h"
#include "graphic/CPT_rendererManager.h"
#include "CPT_event.h"
#include "graphic/CPT_graphic.h"

#include "components/C_transform.h"
#include "components/C_sprite.h"


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