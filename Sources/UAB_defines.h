#ifndef _UAB_DEFINES_H
#define _UAB_DEFINES_H

#include <SDL.h>
#include <SDL_image.h>

#include "CPT_utils.h"
#include "CPT_vec2f.h"
#include "UAB_events.h"

#include "C_rigidbody.h"
#include "C_player.h"
#include "C_animation.h"
#include "C_sprite.h"
#include "C_screenPosition.h"
#include "C_collider.h"
#include "C_transform.h"
#include "C_particuleEmitter.h"
#include "C_explosion.h"

#define ALL_EXCEPT_BOMBS_LAYER  0
#define BOMBS_LAYER             1

#define ENTITY_TYPE_PLAYER_ONE  0
#define ENTITY_TYPE_PLAYER_TWO  1

#define ENTITY_TYPE_BOMB        10
#define ENTITY_TYPE_MISSILE     11

#define DEAD_ZONE_STICK         5000
#define STICK_MAX_VALUE         32767

class ActorFactory : public Singleton<ActorFactory> {
    friend class Singleton <ActorFactory>;

private:
    SDL_Texture         *m_pSpriteSheet;
    SDL_Texture         *m_pBackground;

    AnimatedSprite      *m_playerOneAnimation;
    AnimatedSprite      *m_playerTwoAnimation;
    AnimatedSprite      *m_explosion;
    Sprite              *m_smoke;
    Sprite              *m_missile;
    Sprite              *m_bomb;
    Sprite              *m_background;

public:
    void initialize() override {
        loadResources();
        std::vector<SDL_Rect> frames = std::vector<SDL_Rect>();
        SDL_Rect frame1; frame1.x = 0; frame1.y = 0; frame1.w = 132; frame1.h = 70; frames.push_back(frame1);
        SDL_Rect frame2; frame2.x = 132; frame2.y = 0; frame2.w = 132; frame2.h = 70; frames.push_back(frame2);
        SDL_Rect frame3; frame3.x = 264; frame3.y = 0; frame3.w = 132; frame3.h = 70; frames.push_back(frame3);
        SDL_Rect frame4; frame4.x = 396; frame4.y = 0; frame4.w = 132; frame4.h = 70; frames.push_back(frame4);
        std::vector<SDL_Rect> frames2 = std::vector<SDL_Rect>();
        frame1; frame1.x = 0; frame1.y = 70; frame1.w = 132; frame1.h = 70; frames2.push_back(frame1);
        frame2; frame2.x = 132; frame2.y = 70; frame2.w = 132; frame2.h = 70; frames2.push_back(frame2);
        frame3; frame3.x = 264; frame3.y = 70; frame3.w = 132; frame3.h = 70; frames2.push_back(frame3);
        frame4; frame4.x = 396; frame4.y = 70; frame4.w = 132; frame4.h = 70; frames2.push_back(frame4);

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
        m_smoke = new Sprite(m_pSpriteSheet, 30, 140, 30, 30);
        m_missile = new Sprite(m_pSpriteSheet, 30, 172, 26, 22);
        m_bomb = new Sprite(m_pSpriteSheet, 0, 140, 30, 60);
    }

    entityID createBackground(EntityManager& em) {
        entityID background = em.createEntity();
        em.addComponent(background, new CScreenPosition(640, 360));
        em.addComponent(background, new CTransform(640, 360));
        em.addComponent(background, new CSprite(m_background, 0));
        
        return background;
    }
    
    entityID createPlayerOne(EntityManager& em) {
        entityID playerOne = em.createEntity();
        em.addComponent(playerOne, new CPlayer());
        em.addComponent(playerOne, new CScreenPosition(200, 200));
        em.addComponent(playerOne, new CTransform(200, 200));
        em.addComponent(playerOne, new CRigidBody(0.5f, false));
        em.addComponent(playerOne, new CAnimation(m_playerOneAnimation, 110.0f, 3));
        em.addComponent(playerOne, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 40, new PlayerCollideFunctor()));

        return playerOne;
    }

    entityID createPlayerTwo(EntityManager& em) {
        entityID playerTwo = em.createEntity();
        em.addComponent(playerTwo, new CPlayer());
        em.addComponent(playerTwo, new CScreenPosition(500, 500));
        em.addComponent(playerTwo, new CTransform(500, 500));
        em.addComponent(playerTwo, new CRigidBody(0.5f, false));
        em.addComponent(playerTwo, new CAnimation(m_playerTwoAnimation, 110.0f, 3));
        em.addComponent(playerTwo, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 40, new PlayerCollideFunctor()));

        return playerTwo;
    }

    entityID createMissile(EntityManager& em, Vec2f direction, Vec2f location, int angle) {
        entityID missile = em.createEntity();

        CRigidBody *rb = new CRigidBody(true);
        rb->m_velocity.addScaledVector(direction, 400);

        em.addComponent(missile, new CSprite(m_missile, 3));
        em.addComponent(missile, new CScreenPosition(location.getX(), location.getY()));
        em.addComponent(missile, new CTransform(location.getX(), location.getY(), angle));
        em.addComponent(missile, rb);
        em.addComponent(missile, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 20, 100));
        em.addComponent(missile, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 12, new MissileCollideFunctor()));

        return missile;
    }
    
    entityID createBomb(EntityManager& em, int x) {
        entityID bomb = em.createEntity();
        em.addComponent(bomb, new CSprite(m_bomb, 3));
        em.addComponent(bomb, new CScreenPosition(x, -100));
        em.addComponent(bomb, new CTransform(x, -100));
        em.addComponent(bomb, new CRigidBody(true));
        em.addComponent(bomb, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 10, 100));
        em.addComponent(bomb, new CCollider(BOMBS_LAYER, 25, new BombCollideFunctor()));

        return bomb;
    }

    entityID createExplosion(EntityManager& em, Vec2f location) {
        entityID explosion = em.createEntity();
        em.addComponent(explosion, new CAnimation(m_explosion, 80, true, false, 3));
        em.addComponent(explosion, new CScreenPosition(location.getX(), location.getY()));
        em.addComponent(explosion, new CTransform(location.getX(), location.getY(), 0));
        //em.addComponent(explosion, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 50, new ExplosionCollideFunctor()));
        em.addComponent(explosion, new CExplosion());

        return explosion;
    }

private:
    void loadResources() {
        int imgFlags = IMG_INIT_PNG;
        assert(IMG_Init(imgFlags) & imgFlags);

        SDL_Surface *surface = IMG_Load("../Resources/UAB_spritesheet.png");
        assert(surface != NULL);
        this->m_pSpriteSheet = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);

        surface = IMG_Load("../Resources/background.png");
        assert(surface != NULL);
        this->m_pBackground = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);

        SDL_FreeSurface(surface);
        assert(this->m_pSpriteSheet != NULL);
    }
};

#endif