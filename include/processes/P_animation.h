#ifndef _P_ANIMATION_PROCESS_H_
#define _P_ANIMATION_PROCESS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "CPT_process.h"
#include "core/CPT_time.h"
#include "entity/CPT_entity.h"
#include "graphic/CPT_rendererManager.h"
#include "graphic/CPT_graphic.h"

#include "components/C_transform.h"
#include "components/C_animation.h"

class PAnimation : public UpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PAnimation() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void v_updateEntity(entityID id, const GameTime& gameTime);
    void v_destroy();
};
#endif