#ifndef _C_ANIMATION_H_
#define _C_ANIMATION_H_

#include <vector>

#include <SDL.h>

#include "CPT_component.h"
#include "CPT_graphic.h"

using namespace std;

class CAnimation : public IComponent {

public:
    static const ComponentType sk_componentType = 0x10edddc8;

    AnimatedSprite          *m_animation;
    bool                    m_bActivated;
    bool                    m_bLoop;
    int                     m_currentFrame;
    double                  m_elapsedTime;
    float                   m_frameDuration;
    int                     m_layer;

    CAnimation(AnimatedSprite *animation, float frameDuration, int layer) :
        m_animation(animation), 
        m_frameDuration(frameDuration), 
        m_currentFrame(0), 
        m_elapsedTime(0), 
        m_bLoop(true), 
        m_bActivated(true),
        m_layer(layer) {}

    CAnimation(AnimatedSprite *animation, float frameDuration, bool activated, bool loop, int layer) :
        m_animation(animation), 
        m_frameDuration(frameDuration), 
        m_currentFrame(0), 
        m_elapsedTime(0), 
        m_bLoop(loop), 
        m_bActivated(activated),
        m_layer(layer) {}

    virtual ~CAnimation() {}

    inline const ComponentType getComponentType(void) const {
        return CAnimation::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CSprite";
    }
};

#endif