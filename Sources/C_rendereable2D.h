#ifndef _C_RENDERABLE_2D_H_
#define _C_RENDERABLE_2D_H_

#include <SDL2/SDL.h>
#include "CPT_component.h"

class CRendereable2D : public IComponent {

private:
    float                       m_alpha = 1;
    int                         m_order = 0;
    SDL_RendererFlip            m_flip = SDL_FLIP_NONE;

public:
    static const ComponentType  sk_componentType;

    virtual SDL_Texture*        getTexture() const = 0;
    virtual SDL_Rect            getSource() const = 0;
    virtual int                 getWidth() const = 0;
    virtual int                 getHeight() const = 0;


    float                       getAlpha() const { return m_alpha; }
    void                        setAlpha(float alpha) { m_alpha = alpha; }
    int                         getOrder() const { return m_alpha; }
    void                        setOrder(int order) { m_order = order; }
    SDL_RendererFlip            getFlip() const { return m_flip; }
    void                        SetFlip(SDL_RendererFlip flip) { m_flip = flip; }

    inline const ComponentType getComponentType(void) const {
        return CRendereable2D::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CRenderable2D";
    }
};

#endif