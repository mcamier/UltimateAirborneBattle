#include "P_shapeRender.h"

#include "C_shape.h"
#include "c_screenPosition.h"

ComponentType e[] = { CScreenPosition::sk_componentType, CShape::sk_componentType };
const std::vector<ComponentType> PShapeRender::sk_requirements(e, e + 2);

void PShapeRender::v_processRender(entityID id, const GameTime& gameTime) {
    CShape *shape = getEntityAs<CShape>(id);
    CScreenPosition *position = getEntityAs<CScreenPosition>(id);

    SDL_Rect dest;
    dest.x = position->m_pData->getX(); dest.y = position->m_pData->getY();
    dest.w = shape->m_rect.w; dest.h = shape->m_rect.h;

    RendererManager::get()->renderRectangle(true, dest, shape->m_color);
}