#ifndef _UAB_P_GAME_MANAGER_H_
#define _UAB_P_GAME_MANAGER_H_


#include <iostream>
#include <SDL.h>

#include "CPT_process.h"
#include "CPT_command.h"
#include "CPT_graphic.h"
#include "CPT_inputHandler.h"
#include "C_rigidbody.h"
#include "C_transform.h"

#include "UAB_math.h"

class PGameManager : public UpdateProcess {
public:
    SDL_Texture         *m_pSpriteSheet;
    SDL_Texture         *m_pExplosion;

    entityID            m_playerOne;
    entityID            m_playerTwo;

    AnimatedSprite      *m_playerOneAnimation;
    AnimatedSprite      *m_playerTwoAnimation;
    AnimatedSprite      *m_explosion;
    Sprite              *m_smoke;
    Sprite              *m_missile;
    Sprite              *m_bomb;
    Sprite              *m_background;
    
    int                 m_bombSpawnRate = 9000;
    int                 m_bombTiming = 0;

    Delegate<IEvent*>   d_missileFired;

    Delegate<IEvent*>   d_inputFire;
    Delegate<IEvent*>   d_inputThrust;
    Delegate<IEvent*>   d_inputOrientation;

public:
                        PGameManager() {}
    virtual             ~PGameManager() {}

    inline const unsigned int getID() const { return 10001; }

    void                v_initialize(void);
    void                v_update(const GameTime& gameTime);
    void                v_destroy(void) {}

private:
    void                loadResources();
    void                onMissileFired(IEvent *eventData);
    void                onInputFire(IEvent *eventData);
    void                onInputThrust(IEvent *eventData);
    void                onInputOrientation(IEvent *eventData);
};
#endif