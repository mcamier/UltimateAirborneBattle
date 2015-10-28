#include "IParticule.h"

#include "CPT_graphic.h"
#include "CPT_rendererManager.h"


/**************************************/
/*            Base Particule          */
/**************************************/
bool IParticule::isDead(void) {
    return (m_elapsed >= m_lifetime);
}

void IParticule::update(const GameTime& gameTime) {
    m_elapsed += gameTime.getElapsedMillisecond();

    if (!isDead()) {
        m_x += m_vx * gameTime.getElapsedSecond();
        m_y += m_vy * gameTime.getElapsedSecond();

        if (m_gravityApplied){
            m_vx += 0;
            m_vy += 5.0f;
        }
    }
}

/**************************************/
/*        Animated Particule          */
/**************************************/
PoolAllocator AnimatedParticule::poolAllocator = PoolAllocator(sizeof(AnimatedParticule), 5000);

void AnimatedParticule::update(const GameTime& gameTime) {
    IParticule::update(gameTime);
    if (m_bActivated) {
        if (m_animationElapsedTime >= m_frameDuration) {
            m_currentFrame++;
            if (m_currentFrame >= m_pAnimation->getFrameCount()) {

                if (m_bLoop == false) {
                    m_bActivated = false;
                }
                else {
                    m_currentFrame = 0;
                }
            }
            m_animationElapsedTime = 0;
        }
        else {
            m_animationElapsedTime += gameTime.getElapsedMillisecond();
        }
    }
}

void AnimatedParticule::draw(const GameTime& gameTime) {
    SDL_Rect dest;
    dest.x = m_x - m_pAnimation->getWidth(m_currentFrame) / 2;
    dest.y = m_y - m_pAnimation->getHeight(m_currentFrame) / 2;
    dest.w = m_pAnimation->getWidth(m_currentFrame);
    dest.h = m_pAnimation->getHeight(m_currentFrame);

    RendererManager::get()->renderTexture(
        2,
        m_pAnimation->getTexture(),
        m_pAnimation->getFrame(m_currentFrame),
        &dest,
        0,
        SDL_RendererFlip::SDL_FLIP_NONE,
        1);
}

AnimatedParticule* AnimatedParticule::cloneIntoPool(void) {
    if (!AnimatedParticule::poolAllocator.isInitialized()) {
        AnimatedParticule::poolAllocator.initialize();
    }
     
    void* ptr = AnimatedParticule::poolAllocator.alloc();
    if (ptr != nullptr) {
        return new (ptr)AnimatedParticule(this->m_pAnimation, this->m_frameDuration);
    }
    return nullptr;
}

void AnimatedParticule::removeFromPool() {
    if (!AnimatedParticule::poolAllocator.isInitialized()) {
        AnimatedParticule::poolAllocator.initialize();
    }
    return AnimatedParticule::poolAllocator.free(this);
}


/**************************************/
/*          Sprite Particule          */
/**************************************/
PoolAllocator SpriteParticule::poolAllocator = PoolAllocator(sizeof(SpriteParticule), 5000);

void SpriteParticule::update(const GameTime& gameTime){
    IParticule::update(gameTime);
}

void SpriteParticule::draw(const GameTime&) {
    SDL_Rect dest;
    dest.x = m_x - m_pSprite->getWidth() / 2;
    dest.y = m_y - m_pSprite->getHeight() / 2;
    dest.w = m_pSprite->getWidth();
    dest.h = m_pSprite->getHeight();

    RendererManager::get()->renderTexture(
        2,
        m_pSprite->getTexture(),
        m_pSprite->getSourceRect(),
        &dest,
        0,
        SDL_RendererFlip::SDL_FLIP_NONE,
        1 - (m_elapsed / m_lifetime));
}

SpriteParticule* SpriteParticule::cloneIntoPool(void) {
    if (!SpriteParticule::poolAllocator.isInitialized()) {
        SpriteParticule::poolAllocator.initialize();
    }

    void* ptr = SpriteParticule::poolAllocator.alloc();
    if (ptr != nullptr) {
        return new (ptr)SpriteParticule(this->m_pSprite);
    }
    return nullptr;
}

void SpriteParticule::removeFromPool() {
    if (!SpriteParticule::poolAllocator.isInitialized()) {
        SpriteParticule::poolAllocator.initialize();
    }
    return SpriteParticule::poolAllocator.free(this);
}