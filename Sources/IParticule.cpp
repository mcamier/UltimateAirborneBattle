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
PoolAllocator AnimatedParticule::poolAllocator = PoolAllocator(sizeof(AnimatedParticule), 10000);

void AnimatedParticule::update(const GameTime& gameTime) {
    IParticule::update(gameTime);
    // update animation
}

void AnimatedParticule::draw(const GameTime& gameTime) { }

AnimatedParticule* AnimatedParticule::clone(void) {
    AnimatedParticule* ptr = new AnimatedParticule(m_pAnimation);
    return ptr;
}

void * AnimatedParticule::operator new(size_t size){
    if (!AnimatedParticule::poolAllocator.isInitialized()) {
        AnimatedParticule::poolAllocator.initialize();
    }
    return AnimatedParticule::poolAllocator.alloc();
}

void AnimatedParticule::operator delete(void * pMem) {
    if (!AnimatedParticule::poolAllocator.isInitialized()) {
        AnimatedParticule::poolAllocator.initialize();
    }
    return AnimatedParticule::poolAllocator.free(pMem);
}


/**************************************/
/*          Sprite Particule          */
/**************************************/
PoolAllocator SpriteParticule::poolAllocator = PoolAllocator(sizeof(SpriteParticule), 10000);

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
        3,
        m_pSprite->getTexture(),
        m_pSprite->getSourceRect(),
        &dest,
        0,
        SDL_RendererFlip::SDL_FLIP_NONE,
        1 - (m_elapsed / m_lifetime));
}

SpriteParticule* SpriteParticule::clone(void) {
    SpriteParticule* ptr = new SpriteParticule(m_pSprite);
    return ptr;
}

void * SpriteParticule::operator new(size_t size){
    if (!SpriteParticule::poolAllocator.isInitialized()) {
        SpriteParticule::poolAllocator.initialize();
    }
    return SpriteParticule::poolAllocator.alloc();
}

void SpriteParticule::operator delete(void * pMem) {
    if (!SpriteParticule::poolAllocator.isInitialized()) {
        SpriteParticule::poolAllocator.initialize();
    }
    return SpriteParticule::poolAllocator.free(pMem);
}