#include "processes/P_animation.h"

#include <math.h>
#include "math.h"

ComponentType c[] = { CAnimation::sk_componentType };
const std::vector<ComponentType> PAnimation::sk_requirements(c, c + 1);

void PAnimation::v_updateEntity(entityID id, const GameTime& gameTime) {
    CAnimation *anim = getEntityAs<CAnimation>(id);

    if (anim->m_bActivated) {
        if (anim->m_elapsedTime >= anim->m_frameDuration) {
            anim->m_currentFrame++;
            if (anim->m_currentFrame >= anim->m_animation->get()->getFrameCount()) {
                
                if (anim->m_bLoop == false) {
                    anim->m_bActivated = false;
                } else {
                    anim->m_currentFrame = 0;
                }
            }
            anim->m_elapsedTime = 0;
        }
        else {
            anim->m_elapsedTime += gameTime.getElapsedMillisecond();
        }
    }
}

void PAnimation::v_destroy() {}