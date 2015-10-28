#ifndef _P_ANIMATION_PROCESS_H_
#define _P_ANIMATION_PROCESS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_rendererManager.h"
#include "CPT_graphic.h"

#include "C_transform.h"
#include "C_animation.h"

class PAnimation : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PAnimation() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int getID() const;
    void v_updateEntity(entityID id, const GameTime& gameTime);
    void v_destroy();
};
#endif