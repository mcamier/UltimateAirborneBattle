#ifndef _C_ANIMATION_H_
#define _C_ANIMATION_H_

#include <vector>
#include <SDL2/SDL.h>
#include "C_rendereable2D.h"
#include "CPT_component.h"
#include "CPT_graphic.h"

using namespace std;

class CAnimation : public CRendereable2D {
    friend class PAnimation;

private:
    AnimatedSprite          *m_animation;
    bool                    m_bActivated;
    bool                    m_bLoop;
    int                     m_currentFrame;
    double                  m_elapsedTime;
    float                   m_frameDuration;

public:
    CAnimation() {}

    CAnimation(AnimatedSprite *animation, int order, float frameDuration, bool activated, bool loop) :
        m_animation(animation), 
        m_frameDuration(frameDuration), 
        m_currentFrame(0), 
        m_elapsedTime(0), 
        m_bLoop(loop), 
        m_bActivated(activated) {
    
        this->setOrder(order);
    }

    virtual ~CAnimation() {}

    SDL_Texture*            getTexture() const override { return m_animation->getTexture(); }
    SDL_Rect                getSource() const override { return m_animation->getFrame(m_currentFrame); }
    int                     getWidth() const override { return m_animation->getWidth(m_currentFrame); }
    int                     getHeight() const override { return m_animation->getHeight(m_currentFrame); }

    static const char* getName(void) {
        return "CAnimation";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};


class CAnimationCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(const rapidjson::Value& node) {
        return new CAnimation();
    }
};

#endif