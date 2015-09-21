#ifndef _C_SPRITE_H_
#define _C_SPRITE_H_

#include <SDL.h>
#include "CPT_component.h"

class CSprite : public IComponent {

public:
    static const ComponentType sk_componentType = 0x44a7aa1a;

    Sprite         *m_pSprite;
    int             m_layer;

    CSprite(Sprite *sprite, int layer) : m_pSprite(sprite), m_layer(layer) {}

    virtual ~CSprite() {}

    inline const ComponentType getComponentType(void) const {
        return CSprite::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CSprite";
    }
};

#endif