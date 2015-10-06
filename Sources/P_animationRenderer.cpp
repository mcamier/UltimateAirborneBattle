#include <math.h>

#include "P_animationRenderer.h"
#include "C_screenPosition.h"

ComponentType c[] = { CAnimation::sk_componentType, CScreenPosition::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PAnimationRenderer::sk_requirements(c, c + 3);

const unsigned int PAnimationRenderer::getID() const {
    return 10007;
}

void PAnimationRenderer::v_processRender(entityID id, const GameTime& gameTime) {
    CAnimation *anim = getEntityAs<CAnimation>(id);
    CTransform *transform = getEntityAs<CTransform>(id);
    CScreenPosition *position = getEntityAs<CScreenPosition>(id);

    SDL_Rect dest;
    dest.x = position->m_pData->x - anim->m_animation->getWidth(anim->m_currentFrame)/2;
    dest.y = position->m_pData->y - anim->m_animation->getHeight(anim->m_currentFrame) / 2;
    dest.w = anim->m_animation->getWidth(anim->m_currentFrame) * transform->m_scale.x;
    dest.h = anim->m_animation->getHeight(anim->m_currentFrame) * transform->m_scale.y;

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
    SDL_Rect source = anim->m_animation->getFrame(anim->m_currentFrame);

    RendererManager::get()->renderAnimation(
        anim->m_animation, 
        &source, 
        &dest, 
        transform->m_rotation,
        anim->m_hflip,
        anim->m_vflip,
        1, 
        anim->m_layer);
}

void PAnimationRenderer::v_destroy() {}