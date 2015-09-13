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

#include "C_rigidbody.h"
#include "C_player.h"
#include "C_animation.h"
#include "C_sprite.h"
#include "C_screenPosition.h"
#include "C_shape.h"
#include "C_transform.h"
#include "C_particuleEmitter.h"

#include "UAB_math.h"

void PGameManager::v_initialize() {
    loadResources();
    std::vector<SDL_Rect> frames = std::vector<SDL_Rect>();
    SDL_Rect frame1; frame1.x = 0; frame1.y = 0; frame1.w = 74; frame1.h = 43; frames.push_back(frame1);
    SDL_Rect frame2; frame2.x = 74; frame2.y = 0; frame2.w = 74; frame2.h = 43; frames.push_back(frame2);
    SDL_Rect frame3; frame3.x = 148; frame3.y = 0; frame3.w = 74; frame3.h = 43; frames.push_back(frame3);
    SDL_Rect frame4; frame4.x = 222; frame4.y = 0; frame4.w = 74; frame4.h = 43; frames.push_back(frame4);

    m_background = new Sprite(m_pBackground, 0, 0, 640, 360);
    m_playerOneAnimation = new AnimatedSprite(m_pSpriteSheet, frames, 4);
    m_smoke = new Sprite(m_pSpriteSheet, 15, 43, 15, 16);
    m_missile = new Sprite(m_pSpriteSheet, 15, 59, 13, 11);
    m_bomb = new Sprite(m_pSpriteSheet, 0, 43, 15, 30);

    /* create background */
    //entityID background = getScene().getEntityManager().createEntity();
    //getScene().getEntityManager().addComponent(background, new CScreenPosition(0, 0));
    //getScene().getEntityManager().addComponent(background, new CTransform(0, 0));
    //getScene().getEntityManager().addComponent(background, new CSprite(m_background));

    /* create player */
    m_playerOne = getScene().getEntityManager().createEntity();
    getScene().getEntityManager().addComponent(m_playerOne, new CPlayer());
    getScene().getEntityManager().addComponent(m_playerOne, new CScreenPosition(0, 0));
    getScene().getEntityManager().addComponent(m_playerOne, new CTransform(50, 50));
    getScene().getEntityManager().addComponent(m_playerOne, new CRigidBody(0.5f, false));
    getScene().getEntityManager().addComponent(m_playerOne, new CAnimation(m_playerOneAnimation, 110.0f));
    getScene().getEntityManager().addComponent(m_playerOne, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 20, 100));
    
    // commands binding
    inputEvent_t ThrustInput; 
    ThrustInput.keyCode = SDL_SCANCODE_SPACE; 
    ThrustInput.eventType = CPT_HELD;

    inputEvent_t IncreaseAngleInput; 
    IncreaseAngleInput.keyCode = SDL_SCANCODE_UP; 
    IncreaseAngleInput.eventType = CPT_HELD;

    inputEvent_t DecreaseAngleInput; 
    DecreaseAngleInput.keyCode = SDL_SCANCODE_DOWN; 
    DecreaseAngleInput.eventType = CPT_HELD;

    getScene().getInputHandler().registerInput(ThrustInput, new ThrustCommand(getScene().getEntityManager(), m_playerOne));
    getScene().getInputHandler().registerInput(IncreaseAngleInput, new IncreaseAngleCommand(getScene().getEntityManager(), m_playerOne));
    getScene().getInputHandler().registerInput(DecreaseAngleInput, new DecreaseAngleCommand(getScene().getEntityManager(), m_playerOne));
    
}

void PGameManager::v_update(const GameTime& gameTime) {

    if (m_bombTiming > 3000) {
        m_bombTiming = 0;

        int x = MathUtils::randint(640);
        
        entityID bomb = getScene().getEntityManager().createEntity();
        getScene().getEntityManager().addComponent(bomb, new CSprite(m_bomb));
        getScene().getEntityManager().addComponent(bomb, new CScreenPosition(x, -100));
        getScene().getEntityManager().addComponent(bomb, new CTransform(x, -100));
        getScene().getEntityManager().addComponent(bomb, new CRigidBody(true));
        getScene().getEntityManager().addComponent(bomb, new CParticuleEmitter(m_smoke, 700, Vec2f(0, -120), 20, 100));
    }
    else {
        m_bombTiming += gameTime.getElapsedMillisecond();
    } 

}


void PGameManager::loadResources() {
    int imgFlags = IMG_INIT_PNG;
    assert(IMG_Init(imgFlags) & imgFlags);

    SDL_Surface *surface = IMG_Load("../Resources/UAB_red_player.png");
    assert(surface != NULL);
    this->m_pSpriteSheet = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);

    surface = IMG_Load("../Resources/background.png");
    assert(surface != NULL);
    this->m_pBackground = SDL_CreateTextureFromSurface(RendererManager::get()->getRenderer(), surface);


    SDL_FreeSurface(surface);
    assert(this->m_pSpriteSheet != NULL);
}
