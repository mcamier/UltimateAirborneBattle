#ifndef _UAB_SCORE_SCENE_H_
#define _UAB_SCORE_SCENE_H_

#include <assert.h>
#include "CPT_scene.h"

#include "UAB_defines.h"
#include "P_physic.h"
#include "P_player.h"
#include "P_gameManager.h"
#include "P_particuleRenderer.h"
#include "P_animationRenderer.h"
#include "P_spriteRenderer.h"
#include "P_particuleManager.h"
#include "P_collider.h"
#include "P_explosion.h"

class UABScoreScene : public Scene {
public:
    UABScoreScene() : Scene("GAME screen", false, false, "../Resources/inputs/inputs_game.xml") {}

    const unsigned int getID() const { return 10005; }

protected:
    void initialize(void) {
        assert(ActorFactory::get() != NULL);

        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(200, 244));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(544, 700));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(35, 244));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(580, 125));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(402, 370));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(222, 244));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(358, 666));
        ActorFactory::get()->createExplosion(this->getEntityManager(), Vec2f(1000, 54));

        this->addProcess(new PExplosion());

        this->addRenderProcess(new PAnimationRenderer());
        this->addRenderProcess(new PSpriteRenderer());

        std::cout << " UABScoreScene initialized " << std::endl;
    }
};

#endif