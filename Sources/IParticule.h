#ifndef _UAB_IPARTICULE_H_
#define _UAB_IPARTICULE_H_

#include "CPT_graphic.h"
#include "CPT_time.h"
#include "CPT_memory.h"


/**************************************/
/*            Base Particule          */
/**************************************/
class IParticule {

public:
    float               m_elapsed;
    float               m_lifetime;
    float               m_x;
    float               m_y;
    float               m_vx;
    float               m_vy;
    bool                m_gravityApplied;

public:
    virtual ~IParticule() {}
    
    bool                isDead      (void);
    virtual void        update      (const GameTime& gameTime);
    virtual void        draw        (const GameTime& gameTime) = 0;
    virtual IParticule* clone       (void) = 0;
};


/**************************************/
/*        Animated Particule          */
/**************************************/
class AnimatedParticule : public IParticule {

public:
    static const int    TYPE = 1;

private:
    AnimatedSprite      *m_pAnimation;
    static PoolAllocator       poolAllocator;

public:
    AnimatedParticule(AnimatedSprite *animation) : m_pAnimation(animation) {}
    virtual ~AnimatedParticule() {}

    void                update          (const GameTime& gameTime) override;
    void                draw            (const GameTime& gameTime) override;
    AnimatedParticule*  clone           (void) override;

    static void         *operator new   (size_t size);
    static void         operator delete (void * pMem);
};


/**************************************/
/*          Sprite Particule          */
/**************************************/
class SpriteParticule : public IParticule {

public:
    static const int    TYPE = 2;

private:
    Sprite              *m_pSprite;
    static PoolAllocator       poolAllocator;

public:
    SpriteParticule(Sprite *sprite) : m_pSprite(sprite) {}
    virtual ~SpriteParticule() {}

    void                update          (const GameTime& gameTime) override;
    void                draw            (const GameTime& gameTime) override;
    SpriteParticule*    clone           (void) override;

    static void         *operator new   (size_t size);
    static void         operator delete (void * pMem);
};

#endif