#ifndef _TILE_PROCESS_H_
#define _TILE_PROCESS_H_



#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_rendererManager.h"
#include "CPT_event.h"
#include "CPT_graphic.h"

#include "C_transform.h"
#include "C_sprite.h"


class PSpriteRenderer : public EntityRenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PSpriteRenderer() {}
    virtual ~PSpriteRenderer() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int getID() const;
    void v_processRender(entityID id, const GameTime& gameTime);
    void v_destroy();
};

#endif