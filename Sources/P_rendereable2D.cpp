#include "P_rendereable2D.h"

#include "CPT_math.h"

#include "C_rendereable2D.h"
#include "C_screenPosition.h"
#include "C_transform.h"
#include "C_animation.h"

ComponentType jj[] = { CRendereable2D::sk_componentType, CScreenPosition::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PRendereable2D::sk_requirements(jj, jj + 3);

const unsigned int PRendereable2D::getID() const {
    return 10017;
}

void PRendereable2D::v_renderEntity(entityID id, const GameTime& gameTime) {
    CRendereable2D *rendereable = getEntityAs<CRendereable2D>(id);
    CTransform *transform = getEntityAs<CTransform>(id);
    CScreenPosition *position = getEntityAs<CScreenPosition>(id);
    
    SDL_Rect dest;
    dest.x = transform->getX() - rendereable->getWidth() / 2;
    dest.y = transform->getY() - rendereable->getHeight() / 2;
    dest.w = rendereable->getWidth() * transform->getScaleX();
    dest.h = rendereable->getHeight() * transform->getScaleY();

    RendererManager::get()->renderTexture(
        rendereable->getTexture(),
        &rendereable->getSource(),
        &dest,
        MathUtils::radToDeg(transform->getRotation()),
        rendereable->getFlip(),
        rendereable->getAlpha());
}

void PRendereable2D::v_destroy() {}