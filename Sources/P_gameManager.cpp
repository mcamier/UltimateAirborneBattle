#include "P_gameManager.h"

#include <math.h>
#include <random>
#include <assert.h>

#include <SDL.h>
#include <SDL_image.h>

#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_event.h"
#include "CPT_scene.h"
#include "CPT_rendererManager.h"
#include "CPT_vec2f.h"

#include "C_rigidbody.h"
#include "C_player.h"
#include "C_animation.h"
#include "C_sprite.h"
#include "C_screenPosition.h"
#include "C_collider.h"
#include "C_transform.h"
#include "C_particuleEmitter.h"
#include "C_playerInputHandler.h"

#include "UAB_math.h"
#include "UAB_events.h"
#include "UAB_defines.h"


void PGameManager::v_initialize() {
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
            frame.x = j*48*2; 
            frame.y = i*48*2; 
            frame.w = 48*2; 
            frame.h = 48*2; 
            framesEx.push_back(frame);
        }
    }
    

    //m_background = new Sprite(m_pBackground, 0, 0, 640, 360);
    m_explosion = new AnimatedSprite(m_pExplosion, framesEx, 16);
    m_playerTwoAnimation = new AnimatedSprite(m_pSpriteSheet, frames, 4);
    m_playerOneAnimation = new AnimatedSprite(m_pSpriteSheet, frames2, 4);
    m_smoke = new Sprite(m_pSpriteSheet, 30, 140, 30, 30);
    m_missile = new Sprite(m_pSpriteSheet, 30, 172, 26, 22);
    m_bomb = new Sprite(m_pSpriteSheet, 0, 140, 30, 60);

    /* create background 
    entityID background = getScene().getEntityManager().createEntity();
    getScene().getEntityManager().addComponent(background, new CScreenPosition(0, 0));
    getScene().getEntityManager().addComponent(background, new CTransform(0, 0));
    getScene().getEntityManager().addComponent(background, new CSprite(m_background));
*/
    /* create player */
    m_playerOne = getScene().getEntityManager().createEntity();
    getScene().getEntityManager().addComponent(m_playerOne, new CPlayer());
    getScene().getEntityManager().addComponent(m_playerOne, new CScreenPosition(200, 200));
    getScene().getEntityManager().addComponent(m_playerOne, new CTransform(200, 200));
    getScene().getEntityManager().addComponent(m_playerOne, new CRigidBody(0.5f, false));
    getScene().getEntityManager().addComponent(m_playerOne, new CAnimation(m_playerOneAnimation, 110.0f));
    getScene().getEntityManager().addComponent(m_playerOne, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 50, new PlayerCollideFunctor()));

    /* create player */
    m_playerTwo = getScene().getEntityManager().createEntity();
    getScene().getEntityManager().addComponent(m_playerTwo, new CPlayer());
    getScene().getEntityManager().addComponent(m_playerTwo, new CScreenPosition(500, 500));
    getScene().getEntityManager().addComponent(m_playerTwo, new CTransform(500, 500));
    getScene().getEntityManager().addComponent(m_playerTwo, new CRigidBody(0.5f, false));
    getScene().getEntityManager().addComponent(m_playerTwo, new CAnimation(m_playerTwoAnimation, 110.0f));
    getScene().getEntityManager().addComponent(m_playerTwo, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 50, new PlayerCollideFunctor()));

    d_missileFired = Delegate<IEvent*>::make<PGameManager, &PGameManager::onMissileFired>(this);
    EventManager::get()->addListener(MissileFiredEvent::sk_EventType, d_missileFired);

    d_inputFire = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputFire>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputFire);

    d_inputThrust = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputThrust>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputThrust);

    d_inputOrientation = Delegate<IEvent*>::make<PGameManager, &PGameManager::onInputOrientation>(this);
    EventManager::get()->addListener(InputEvent::sk_EventType, d_inputOrientation);
    
}

void PGameManager::v_update(const GameTime& gameTime) {

    if (m_bombTiming > 3000) {
        m_bombTiming = 0;

        int x = MathUtils::randint(1280);
        
        entityID bomb = getScene().getEntityManager().createEntity();
        getScene().getEntityManager().addComponent(bomb, new CSprite(m_bomb));
        getScene().getEntityManager().addComponent(bomb, new CScreenPosition(x, -100));
        getScene().getEntityManager().addComponent(bomb, new CTransform(x, -100));
        getScene().getEntityManager().addComponent(bomb, new CRigidBody(true));
        getScene().getEntityManager().addComponent(bomb, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 10, 100));
        getScene().getEntityManager().addComponent(bomb, new CCollider(BOMBS_LAYER, 25, new BombCollideFunctor()));
    }
    else {
        m_bombTiming += gameTime.getElapsedMillisecond();
    } 

}


void PGameManager::loadResources() {
    int imgFlags = IMG_INIT_PNG;
    assert(IMG_Init(imgFlags) & imgFlags);

    SDL_Surface *surface = IMG_Load("../Resources/UAB_spritesheet.png");
    assert(surface != NULL);
    this->m_pSpriteSheet = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);

    surface = IMG_Load("../Resources/explosion.png");
    assert(surface != NULL);
    this->m_pExplosion = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);


    SDL_FreeSurface(surface);
    assert(this->m_pSpriteSheet != NULL);
}

void PGameManager::onMissileFired(IEvent *eventData) {
    MissileFiredEvent *e = static_cast<MissileFiredEvent*>(eventData);

    float angle = 0;
    if (e->m_direction.getX() != 0 || e->m_direction.getY() != 0) {
       angle = (float)atan2(e->m_direction.getX(), e->m_direction.getY()) * (180 / MathUtils::PI);
    }

    CRigidBody *rb = new CRigidBody(true);
    rb->m_velocity.addScaledVector(e->m_direction, 400);

    entityID missile = getScene().getEntityManager().createEntity();
    getScene().getEntityManager().addComponent(missile, new CSprite(m_missile));
    getScene().getEntityManager().addComponent(missile, new CScreenPosition(e->m_sourcePosition.getX(), e->m_sourcePosition.getY()));
    getScene().getEntityManager().addComponent(missile, new CTransform(e->m_sourcePosition.getX(), e->m_sourcePosition.getY(), angle));
    getScene().getEntityManager().addComponent(missile, rb);
    getScene().getEntityManager().addComponent(missile, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 20, 100));
    getScene().getEntityManager().addComponent(missile, new CCollider(ALL_EXCEPT_BOMBS_LAYER, 12, new MissileCollideFunctor()));

    std::cout << "missile fired" << std::endl;
}


void PGameManager::onInputFire(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_FIRE_EVENT) {
        CPlayer* player = getScene().getEntityManager().getAs<CPlayer>(m_playerOne);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(m_playerOne);
        if (player->m_cooldown <= 0) {
            player->m_cooldown = player->m_defaultCooldown;

            Vec2f direction;
            direction.setX(MathUtils::cosFromDeg(transform->m_rotation)*2);
            direction.setY(MathUtils::sinFromDeg(transform->m_rotation)*2);

            EventManager::get()->queueEvent(new MissileFiredEvent(getScene().getID(), transform->m_position, direction));
        }
    }
}

void PGameManager::onInputThrust(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_THRUST_EVENT) {
        
        CRigidBody* rigidBody = getScene().getEntityManager().getAs<CRigidBody>(m_playerOne);
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(m_playerOne);
        
        Vec2f newVelocity = Vec2f();
        newVelocity.setX(MathUtils::cosFromDeg(transform->m_rotation)*300);
        newVelocity.setY(MathUtils::sinFromDeg(transform->m_rotation)*300);
        
        rigidBody->m_velocity.set(newVelocity.getX(), newVelocity.getY());
    }
}

void PGameManager::onInputOrientation(IEvent *eventData) {
    InputEvent *e = static_cast<InputEvent*>(eventData);

    if (e->m_spaceIDTarget == getScene().getID() && e->m_eventID == INPUT_ORIENTATION_EVENT) {
        CTransform* transform = getScene().getEntityManager().getAs<CTransform>(m_playerOne);
        float floatX, floatY;
        int rawX, rawY;

        rawX = e->m_inputPayload.m_range2D.getX();
        rawY = e->m_inputPayload.m_range2D.getY();

        if (rawX >= DEAD_ZONE_STICK || rawX <= -DEAD_ZONE_STICK) {
            rawX = (rawX > 0) ? rawX - DEAD_ZONE_STICK : rawX + DEAD_ZONE_STICK;
        }
        else { rawX = 0; }

        if (rawY >= DEAD_ZONE_STICK || rawY <= -DEAD_ZONE_STICK) {
            rawY = (rawY > 0) ? rawY - DEAD_ZONE_STICK : rawY + DEAD_ZONE_STICK;
        }
        else { rawY = 0; }
        rawY = -rawY;

        floatX = (rawX != 0) ? rawX / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;
        floatY = (rawY != 0) ? rawY / (float)(STICK_MAX_VALUE - DEAD_ZONE_STICK) : 0;

        int angle = 0;
        if (floatX != 0 || floatY != 0) {
            angle = (float)atan2(floatX, floatY) * (180 / MathUtils::PI);
        }
        angle -= 90;
        if (angle < 0) angle = 360 + angle;

        transform->m_rotation = angle;
    }
    
}