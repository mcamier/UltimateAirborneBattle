#ifndef _UAB_DEFINES_H
#define _UAB_DEFINES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "glm/vec2.hpp"

#include "CPT_utils.h"
#include "UAB_events.h"

#include "components/C_rigidbody.h"
#include "components/C_player.h"
#include "components/C_animation.h"
#include "components/C_sprite.h"
#include "components/C_collider.h"
#include "components/C_transform.h"
#include "components/C_particuleEmitter.h"
#include "components/C_explosion.h"
#include "components/C_missile.h"
#include "components/C_plusOne.h"
#include "collisions_utils.h"
#include "IParticule.h"

#include "core/core.h"
#include "graphic/rendererManager.h"
#include "resource/CPT_resourceManager.h"

#define ALL_EXCEPT_BOMBS_LAYER  0
#define BOMBS_LAYER             1

#define ENTITY_TYPE_PLAYER_ONE  0
#define ENTITY_TYPE_PLAYER_TWO  1

#define ENTITY_TYPE_BOMB        10
#define ENTITY_TYPE_MISSILE     11

#define DEAD_ZONE_STICK         5000
#define STICK_MAX_VALUE         32767

#define RES_BACKGROUND              1
#define RES_SPRITESHEET             2
#define RES_FONT                    3
#define RES_BACKGROUND_SPRITE       4
#define RES_SMOKE_SPRITE            5
#define RES_MISSILE_SPRITE          6
#define RES_BOMB_SPRITE             7
#define RES_PLUS_ONE_SPRITE         8
#define RES_EXPLOSION_ANIMATION     9
#define RES_DARK_SMOKE_ANIMATION    10
#define RES_PLAYER_ONE_ANIMATION    11
#define RES_PLAYER_TWO_ANIMATION    12

using Compote::Core::Locator;

class TempActorFactory : 
    public GameObject {

public:
    static TempActorFactory *m_pInstance;

    ResHandler<SDL_Texture>         *m_pSpriteSheet;
    ResHandler<SDL_Texture>         *m_pBackground;

    ResHandler<AnimatedSprite>      *m_playerTwoAnimation;
    ResHandler<AnimatedSprite>      *m_playerOneAnimation;
    ResHandler<AnimatedSprite>      *m_explosion;
    ResHandler<Sprite>              *m_smoke;
    ResHandler<Sprite>              *m_plusOne;
    ResHandler<Sprite>              *m_missile;
    ResHandler<Sprite>              *m_bomb;
    ResHandler<Sprite>              *m_background;
    ResHandler<AnimatedSprite>      *m_darkSmoke;

public:
    static TempActorFactory *get(void) {
        if (m_pInstance == nullptr) {
            m_pInstance = new TempActorFactory();
            m_pInstance->v_initialize();
        }
        return m_pInstance;
    }

    void v_destroy(void) {}

    bool v_initialize(void) {
        int imgFlags = IMG_INIT_PNG;
        assert(IMG_Init(imgFlags) & imgFlags);

        m_pBackground = Locator::getResourceManager()->get<SDL_Texture>(RES_BACKGROUND);
        m_pSpriteSheet = Locator::getResourceManager()->get<SDL_Texture>(RES_SPRITESHEET);
        m_background = Locator::getResourceManager()->get<Sprite>(RES_BACKGROUND_SPRITE);
        m_explosion = Locator::getResourceManager()->get<AnimatedSprite>(RES_EXPLOSION_ANIMATION);
        m_playerTwoAnimation = Locator::getResourceManager()->get<AnimatedSprite>(RES_PLAYER_TWO_ANIMATION);
        m_playerOneAnimation = Locator::getResourceManager()->get<AnimatedSprite>(RES_PLAYER_ONE_ANIMATION);
        m_darkSmoke = Locator::getResourceManager()->get<AnimatedSprite>(RES_DARK_SMOKE_ANIMATION);
        m_smoke = Locator::getResourceManager()->get<Sprite>(RES_SMOKE_SPRITE);
        m_missile = Locator::getResourceManager()->get<Sprite>(RES_MISSILE_SPRITE);
        m_bomb = Locator::getResourceManager()->get<Sprite>(RES_BOMB_SPRITE);
        m_plusOne = Locator::getResourceManager()->get<Sprite>(RES_PLUS_ONE_SPRITE);

        return 1;
    }

    entityID createBackground(EntityManager& em) {
        entityID background = em.createEntity();
        em.addComponent(background, new CTransform(640.0f, 360.0f));
        em.addComponent(background, new CSprite(m_background, 0));
        
        return background;
    }
    
    entityID createPlayerOne(EntityManager& em, float x, float y) {
        entityID id = createPlayer(em, x, y);
        em.addComponent(id, new CAnimation(m_playerOneAnimation, 3, 110.0f, true, true));
        em.addComponent(id, new CPlayer(glm::vec2(1.0f, .0f)));
        return id;
    }

    entityID createPlayerTwo(EntityManager& em, float x, float y) {
        entityID id = createPlayer(em, x, y);
        em.addComponent(id, new CAnimation(m_playerTwoAnimation, 3, 110.0f, true, true));
        em.addComponent(id, new CPlayer(glm::vec2(-1.0f, .0f)));
        return id;
    }

    entityID createPlayerThree(EntityManager& em, float x, float y) {
        entityID id = createPlayer(em, x, y);
        em.addComponent(id, new CAnimation(m_playerOneAnimation, 3, 110.0f, true, true));
        em.addComponent(id, new CPlayer(glm::vec2(1.0f, .0f)));
        return id;
    }

    entityID createPlayerFour(EntityManager& em, float x, float y) {
        entityID id = createPlayer(em, x, y);
        em.addComponent(id, new CAnimation(m_playerOneAnimation,3, 110.0f, true, true));
        em.addComponent(id, new CPlayer(glm::vec2(-1.0f, .0f)));
        return id;
    }

    entityID createPlayer(EntityManager& em, float x, float y) {
        entityID player = em.createEntity();
        em.addComponent(player, new CTransform(x, y));
        em.addComponent(player, new CRigidBody(false, 0.95f));
        em.addComponent(player, new CCollider(new CircleCollider(40), true, new PlayerCollideFunctor()));
        return player;
    }

    entityID createMissile(entityID throwerID, EntityManager& em, glm::vec2 direction, glm::vec2 location, int angle) {
        entityID missileID = em.createEntity();

        CRigidBody *rb = new CRigidBody(true, 0.99f);
        rb->m_velocity.x += direction.x * 450;
        rb->m_velocity.y += direction.y * 450;

        em.addComponent(missileID, new CSprite(m_missile, 2));
        em.addComponent(missileID, new CTransform(location.x, location.y, angle));
        em.addComponent(missileID, rb);

        //AnimatedParticule *particuleProto = new AnimatedParticule(m_explosion, 80.0f);
        AnimatedParticule *particuleProto = new AnimatedParticule(m_darkSmoke, 90.0f);
        CParticuleEmitter *pe = new CParticuleEmitter(particuleProto, 60, 400.0f, -90, 25, false);
        pe->m_angleVariation = 45;
        pe->m_lifetimeVariation = 50;
        em.addComponent(missileID, pe);
        em.addComponent(missileID, new CCollider(new CircleCollider(12), true, nullptr));
        CMissile *missile = new CMissile();
        missile->m_throwerID = throwerID;
        em.addComponent(missileID, missile);

        return missileID;
    }
    
    entityID createBomb(EntityManager& em, float x) {
        entityID bomb = em.createEntity();
        em.addComponent(bomb, new CSprite(m_bomb, 2));
        em.addComponent(bomb, new CTransform(x, -100.0f));
        em.addComponent(bomb, new CRigidBody(true, 0.99f));

        SpriteParticule *particuleProto = new SpriteParticule(m_smoke);
        CParticuleEmitter *pe = new CParticuleEmitter(particuleProto, 20, 1000, -90, 50, false);
        pe->m_angleVariation = 45;
        em.addComponent(bomb, pe);
        em.addComponent(bomb, new CCollider(new CircleCollider(25), true, new DestructibeColliderFunctor()));

        return bomb;
    }

    entityID createExplosion(EntityManager& em, glm::vec2 location) {
        entityID explosion = em.createEntity();
        em.addComponent(explosion, new CAnimation(m_explosion, 3, 70, true, false));
        em.addComponent(explosion, new CTransform(location.x, location.y, 0, glm::vec2(2.0f, 2.0f)));
        em.addComponent(explosion, new CCollider(new CircleCollider(50), true, nullptr));
        em.addComponent(explosion, new CExplosion());
        //CParticuleEmitter *pe = new CParticuleEmitter(m_smoke, 100, 700, 90, 200, false);
        //pe->m_angleVariation = 45;
        //em.addComponent(explosion, pe);

        return explosion;
    }

    entityID createPlusOne(EntityManager& em, CTransform *offset) {
        entityID id = em.createEntity();
        em.addComponent(id, new CSprite(m_plusOne, 1));
        em.addComponent(id, new CTransform(offset, 0, 0, 0));
        em.addComponent(id, new CPlusOne());
        return id;
    }

    entityID createCamera(EntityManager& em) {
        entityID cam = em.createEntity();
        em.addComponent(cam, new CTransform(0, 0));
        return cam;
    }

private:
    TempActorFactory() {}
    virtual ~TempActorFactory() {}
};

#endif