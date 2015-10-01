#ifndef _UAB_P_GAME_MANAGER_H_
#define _UAB_P_GAME_MANAGER_H_


#include <iostream>
#include <SDL.h>

#include "CPT_process.h"
#include "CPT_graphic.h"
#include "CPT_inputHandler.h"
#include "C_rigidbody.h"
#include "C_transform.h"

#include "UAB_math.h"

enum GameMode {
    ONE_VS_ONE,
    TWO_VS_TWO,
    FFA_THEE_PLAYERS,
    FFA_FOUR_PLAYERS
};

class PGameManager : public UpdateProcess {
public:
    GameMode            m_gameMode;
    bool                m_gameDone = false;

    bool                m_bPlayerOneDead = false;
    bool                m_bPlayerTwoDead = false;
    bool                m_bPlayerThreeDead = false;
    bool                m_bPlayerFourDead = false;

    entityID            m_playerOne = -1;
    entityID            m_playerTwo = -1;
    entityID            m_playerThree = -1;
    entityID            m_playerFour = -1;
    
    int                 m_bombSpawnRate = 9000;
    int                 m_bombTiming = 0;

    Delegate<IEvent*>   d_missileFired;
    Delegate<IEvent*>   d_explosionOccurs;
    Delegate<IEvent*>   d_playerDestroyed;
    Delegate<IEvent*>   d_inputFire;
    Delegate<IEvent*>   d_inputThrust;
    Delegate<IEvent*>   d_inputOrientation;

    std::vector<entityID> m_gameWorldEntities;

public:
                        PGameManager(GameMode gameMode) : m_gameMode(gameMode), m_gameWorldEntities(std::vector<entityID>()){}
    virtual             ~PGameManager() {}

    inline const unsigned int getID() const { return 10001; }

    void                v_initialize(void);
    void                v_update(const GameTime& gameTime);
    void                v_destroy(void) {}


    void                initGame();
    void                initOneVsOne();
    void                initTwoVsTwo();
    void                initThreePlayersFFA();
    void                initFourPlayersFFA();
    bool                isMatchDone();

private:
    void                onMissileFired(IEvent *eventData);
    void                onInputFire(IEvent *eventData);
    void                onInputThrust(IEvent *eventData);
    void                onInputOrientation(IEvent *eventData);
    void                onExplosion(IEvent *eventData);
};
#endif