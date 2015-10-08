#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include "CPT_math.h"
#include "P_spriteRenderer.h"
#include "C_screenPosition.h"

ComponentType b[] = { CSprite::sk_componentType, CScreenPosition::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PSpriteRenderer::sk_requirements(b, b + 3);

const unsigned int PSpriteRenderer::getID() const {
    return 10006;
}

void PSpriteRenderer::v_processRender(entityID id, const GameTime& gameTime) {
    CSprite *sprite = getEntityAs<CSprite>(id);
    CTransform *transform = getEntityAs<CTransform>(id);
    CScreenPosition *position = getEntityAs<CScreenPosition>(id);

    SDL_Rect dest;
    dest.x = transform->m_position.x - sprite->m_pSprite->getWidth()/2;
    dest.y = transform->m_position.y - sprite->m_pSprite->getHeight() / 2;
    dest.w = sprite->m_pSprite->getWidth() * transform->m_scale.x;
    dest.h = sprite->m_pSprite->getHeight() * transform->m_scale.y;

    RendererManager::get()->renderSprite(sprite->m_pSprite, &dest, MathUtils::radToDeg(transform->m_rotation), 1, sprite->m_layer);
}

void PSpriteRenderer::v_destroy() {}