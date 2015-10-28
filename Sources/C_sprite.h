#ifndef _C_SPRITE_H_
#define _C_SPRITE_H_

#include "SDL2/SDL.h"
#include "CPT_component.h"
#include "C_rendereable2D.h"

class CSprite : public CRendereable2D {
    friend class PSpriteRenderer;

private:
    Sprite              *m_pSprite;

public:
                        CSprite(Sprite *sprite, int order) : 
                            m_pSprite(sprite) {
                            
                            this->setOrder(order);
                        }

    virtual             ~CSprite() {}

    SDL_Texture*        getTexture() const override { return m_pSprite->getTexture(); }
    SDL_Rect            getSource() const override { return m_pSprite->getSourceRect(); }
    int                 getWidth() const override { return m_pSprite->getWidth(); }
    int                 getHeight() const override { return m_pSprite->getHeight(); }

    inline const char* getName(void) const {
        return "CSprite";
    }
};

#endif