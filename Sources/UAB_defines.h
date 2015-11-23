#ifndef _UAB_DEFINES_H
#define _UAB_DEFINES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "glm/vec2.hpp"

#include "CPT_utils.h"
#include "UAB_events.h"

#include "C_rigidbody.h"
#include "C_player.h"
#include "C_animation.h"
#include "C_sprite.h"
#include "C_collider.h"
#include "C_transform.h"
#include "C_particuleEmitter.h"
#include "C_explosion.h"
#include "C_missile.h"
#include "C_plusOne.h"
#include "collisions_utils.h"
#include "IParticule.h"

#include "CPT_locator.h"
#include "CPT_rendererManager.h"
#include "CPT_resourceManager.h"

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

class TempActorFactory : 
    public GameService {

public:
    static TempActorFactory *m_pInstance;

    SDL_Texture         *m_pSpriteSheet;
    SDL_Texture         *m_pBackground;

    AnimatedSprite      *m_playerOneAnimation;
    AnimatedSprite      *m_playerTwoAnimation;
    AnimatedSprite      *m_explosion;
    Sprite              *m_smoke;
    Sprite              *m_plusOne;
    Sprite              *m_missile;
    Sprite              *m_bomb;
    Sprite              *m_background;
    AnimatedSprite      *m_darkSmoke;

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
        loadResources();
        std::vector<SDL_Rect>   frames = std::vector<SDL_Rect>();
        SDL_Rect frame1; frame1.x = 0; frame1.y = 0; frame1.w = 132; frame1.h = 70; frames.push_back(frame1);
        SDL_Rect frame2; frame2.x = 132; frame2.y = 0; frame2.w = 132; frame2.h = 70; frames.push_back(frame2);
        SDL_Rect frame3; frame3.x = 264; frame3.y = 0; frame3.w = 132; frame3.h = 70; frames.push_back(frame3);
        SDL_Rect frame4; frame4.x = 396; frame4.y = 0; frame4.w = 132; frame4.h = 70; frames.push_back(frame4);
        SDL_Rect frame5;
        std::vector<SDL_Rect>   frames2 = std::vector<SDL_Rect>();
        frame1; frame1.x = 0;   frame1.y = 70; frame1.w = 132; frame1.h = 70; frames2.push_back(frame1);
        frame2; frame2.x = 132; frame2.y = 70; frame2.w = 132; frame2.h = 70; frames2.push_back(frame2);
        frame3; frame3.x = 264; frame3.y = 70; frame3.w = 132; frame3.h = 70; frames2.push_back(frame3);
        frame4; frame4.x = 396; frame4.y = 70; frame4.w = 132; frame4.h = 70; frames2.push_back(frame4);
        std::vector<SDL_Rect>   frames3 = std::vector<SDL_Rect>();
        frame1; frame1.x = 0;   frame1.y = 384; frame1.w = 68; frame1.h = 62; frames3.push_back(frame1);
        frame2; frame2.x = 68;  frame2.y = 384; frame2.w = 68; frame2.h = 62; frames3.push_back(frame2);
        frame3; frame3.x = 136; frame3.y = 384; frame3.w = 68; frame3.h = 62; frames3.push_back(frame3);
        frame4; frame4.x = 204; frame4.y = 384; frame4.w = 68; frame4.h = 62; frames3.push_back(frame4);
        frame5; frame5.x = 272; frame5.y = 384; frame5.w = 68; frame5.h = 62; frames3.push_back(frame5);

        SDL_Rect frame;
        std::vector<SDL_Rect> framesEx = std::vector<SDL_Rect>();
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                frame.x = j * 96;
                frame.y = i * 96 + 200;
                frame.w = 96;
                frame.h = 96;
                framesEx.push_back(frame);
            }
        }

        m_background = new Sprite(m_pBackground, 0, 0, 1280, 720);
        m_explosion = new AnimatedSprite(m_pSpriteSheet, framesEx, 16);
        m_playerTwoAnimation = new AnimatedSprite(m_pSpriteSheet, frames, 4);
        m_playerOneAnimation = new AnimatedSprite(m_pSpriteSheet, frames2, 4);
        m_darkSmoke = new AnimatedSprite(m_pSpriteSheet, frames3, 5);
        m_smoke = new Sprite(m_pSpriteSheet, 30, 140, 30, 32);
        m_missile = new Sprite(m_pSpriteSheet, 30, 172, 26, 22);
        m_bomb = new Sprite(m_pSpriteSheet, 0, 140, 30, 60);
        m_plusOne = new Sprite(m_pSpriteSheet, 60, 140, 39, 30);

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
    void loadResources() {
        int imgFlags = IMG_INIT_PNG;
        assert(IMG_Init(imgFlags) & imgFlags);

        Locator::getResourceManager()->load(RES_BACKGROUND);
        Locator::getResourceManager()->load(RES_SPRITESHEET);
        this->m_pBackground = Locator::getResourceManager()->get<SDL_Texture>(RES_BACKGROUND);
        this->m_pSpriteSheet = Locator::getResourceManager()->get<SDL_Texture>(RES_SPRITESHEET);

        /*SDL_Surface *surface = IMG_Load("../Resources/UAB_spritesheet.png");
        assert(surface != NULL);
        this->m_pSpriteSheet = SDL_CreateTextureFromSurface(Locator::getRenderer()->getRenderer(), surface);

        surface = IMG_Load("../Resources/background.png");
        assert(surface != NULL);
        this->m_pBackground = SDL_CreateTextureFromSurface(Locator::getRenderer()->getRenderer(), surface);

        SDL_FreeSurface(surface);*/
        assert(this->m_pBackground != NULL);
        assert(this->m_pSpriteSheet != NULL);
    }

    TempActorFactory() {}
    virtual ~TempActorFactory() {}
};

#endif