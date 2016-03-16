#include "processes/P_rendereable2D.h"

#include "CPT_math.h"
#include "CPT_rendererManager.h"

#include "components/C_rendereable2D.h"
#include "components/C_transform.h"
#include "components/C_animation.h"
#include "CPT_locator.h"

ComponentType jj[] = { CRendereable2D::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PRendereable2D::sk_requirements(jj, jj + 2);

const unsigned int PRendereable2D::getID() const {
    return 10017;
}

void PRendereable2D::v_before(const GameTime& gameTime) {
    m_cameraPositionThisFrame.x = 0;
    m_cameraPositionThisFrame.y = 0;
    CTransform* cameraTransform = getScene().getEntityManager().getAs<CTransform>(m_cameraID);
    if (cameraTransform != nullptr) {
        m_cameraPositionThisFrame.x = cameraTransform->getX();
        m_cameraPositionThisFrame.y = cameraTransform->getY();
    }
}

void PRendereable2D::v_renderEntity(entityID id, const GameTime& gameTime) {
    CRendereable2D *rendereable = getEntityAs<CRendereable2D>(id);
    CTransform *transform = getEntityAs<CTransform>(id);
    
    SDL_Rect dest;
    dest.x = (transform->getTransformX() - (rendereable->getWidth() / 2) * transform->getTransformScaleX()) - m_cameraPositionThisFrame.x;
    dest.y = (transform->getTransformY() - (rendereable->getHeight() / 2) * transform->getTransformScaleY()) - m_cameraPositionThisFrame.y;
    dest.w = rendereable->getWidth() * transform->getTransformScaleX();
    dest.h = rendereable->getHeight() * transform->getTransformScaleY();

    Locator::getRenderer()->renderTexture(
        rendereable->getOrder(),
        rendereable->getTexture(),
        rendereable->getSource(),
        &dest,
        MathUtils::radToDeg(transform->getRotation()),
        rendereable->getFlip(),
        rendereable->getAlpha());
}

void PRendereable2D::v_destroy() {}