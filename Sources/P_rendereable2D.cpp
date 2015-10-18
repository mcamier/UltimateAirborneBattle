#include "P_rendereable2D.h"

#include "CPT_math.h"

#include "C_rendereable2D.h"
#include "C_screenPosition.h"
#include "C_transform.h"
#include "C_animation.h"

ComponentType jj[] = { CRendereable2D::sk_componentType, CTransform::sk_componentType };
//ComponentType jj[] = { CRendereable2D::sk_componentType, CScreenPosition::sk_componentType, CTransform::sk_componentType };
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
    //CScreenPosition *position = getEntityAs<CScreenPosition>(id);
    
    SDL_Rect dest;
    dest.x = (transform->getX() - (rendereable->getWidth() / 2) * transform->getScaleX() )- m_cameraPositionThisFrame.x;
    dest.y = (transform->getY() - (rendereable->getHeight() / 2) * transform->getScaleY() )- m_cameraPositionThisFrame.y;
    dest.w = rendereable->getWidth() * transform->getScaleX();
    dest.h = rendereable->getHeight() * transform->getScaleY();

    RendererManager::get()->renderTexture(
        rendereable->getOrder(),
        rendereable->getTexture(),
        rendereable->getSource(),
        &dest,
        MathUtils::radToDeg(transform->getRotation()),
        rendereable->getFlip(),
        rendereable->getAlpha());
}

void PRendereable2D::v_destroy() {}