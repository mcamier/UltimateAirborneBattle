#ifndef _C_SHAPE_H_
#define _C_SHAPE_H_

#include <SDL.h>

#include "CPT_component.h"

class CShape : public IComponent {

public:
    const static ComponentType sk_componentType = 0x6b47e35;

    SDL_Color m_color;
    SDL_Rect m_rect;

    CShape(SDL_Color color, SDL_Rect rect) : m_color(color), m_rect(rect) {}

    virtual ~CShape() {}

    inline const ComponentType getComponentType(void) const {
        return CShape::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CShape";
    }
};

#endif