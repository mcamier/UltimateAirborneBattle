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
    AnimatedSprite      *m_explosion;
    Sprite              *m_smoke;
    Sprite              *m_missile;
    Sprite              *m_bomb;
    Sprite              *m_background;
    
    int                 m_bombSpawnRate = 9000;
    int                 m_bombTiming = 0;

    Delegate<IEvent*>   d_missileFired;

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
};





class FireCommand : public Command {
private:
    entityID m_playerID;
    EntityManager& m_pEntityManager;

public:
    FireCommand(EntityManager& em, entityID playerID) : m_playerID(playerID), m_pEntityManager(em) {}

    void execute(void) const {}
};


class IncreaseAngleCommand : public Command {
private:
    entityID m_playerID;
    EntityManager& m_pEntityManager;

public:
    IncreaseAngleCommand(EntityManager& em, entityID playerID) : m_playerID(playerID), m_pEntityManager(em) {}

    void execute(void) const {
        CTransform *transform = m_pEntityManager.getAs<CTransform>(m_playerID);
        transform->m_rotation += 1;
        if (transform->m_rotation >= 360) transform->m_rotation -= 360;
    }
};


class DecreaseAngleCommand : public Command {
private:
    entityID m_playerID;
    EntityManager& m_pEntityManager;

public:
    DecreaseAngleCommand(EntityManager& em, entityID playerID) : m_playerID(playerID), m_pEntityManager(em) {}

    void execute(void) const {
        CTransform *transform = m_pEntityManager.getAs<CTransform>(m_playerID);
        transform->m_rotation -= 1;
        if (transform->m_rotation < 0) transform->m_rotation = 360;
    }
};


class ThrustCommand : public Command {
private:
    entityID m_playerID;
    EntityManager& m_pEntityManager;

public:
    ThrustCommand(EntityManager& em, entityID playerID) : m_playerID(playerID), m_pEntityManager(em) {}

    void execute(void) const {
        CRigidBody *body = m_pEntityManager.getAs<CRigidBody>(m_playerID);
        CTransform *transform = m_pEntityManager.getAs<CTransform>(m_playerID);

        int x = 1;
        float angle = transform->m_rotation * (MathUtils::PI / 180);

        Vec2f newVelocity;
        newVelocity.setX(x * cos(angle));
        newVelocity.setY(x * sin(angle));
        newVelocity.normalize();
        newVelocity *= 170;

        body->m_velocity = newVelocity;
        body->addForce(newVelocity);
    }
};
#endif