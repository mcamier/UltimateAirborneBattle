#include "P_animation.h"

#include <math.h>
#include "CPT_math.h"
#include "C_screenPosition.h"

ComponentType c[] = { CAnimation::sk_componentType };
const std::vector<ComponentType> PAnimation::sk_requirements(c, c + 1);

const unsigned int PAnimation::getID() const {
    return 10007;
}

void PAnimation::v_process(entityID id, const GameTime& gameTime) {
    CAnimation *anim = getEntityAs<CAnimation>(id);

    if (anim->m_bActivated) {
        if (anim->m_elapsedTime >= anim->m_frameDuration) {
            anim->m_currentFrame++;
            if (anim->m_currentFrame >= anim->m_animation->getFrameCount()) {
                
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