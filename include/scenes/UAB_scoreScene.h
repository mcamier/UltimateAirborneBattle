#ifndef _UAB_SCORE_SCENE_H_
#define _UAB_SCORE_SCENE_H_

#include <assert.h>
#include "CPT_scene.h"

#include "UAB_defines.h"
#include "processes/P_physic.h"
#include "processes/P_player.h"
#include "processes/P_rendereable2D.h"
#include "processes/P_particuleManager.h"
#include "processes/P_explosion.h"

class UABScoreScene : public AbstractScene {
public:
    UABScoreScene() : AbstractScene("GAME screen", false, false) {}

public:
    void initialize(void) {
        assert(TempActorFactory::get() != NULL);

        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(200, 244));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(544, 700));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(35, 244));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(580, 125));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(402, 370));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(222, 244));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(358, 666));
        TempActorFactory::get()->createExplosion(this->getEntityManager(), glm::vec2(1000, 54));

        this->addProcess(new PExplosion());

        this->addRenderProcess(new PRendereable2D(TempActorFactory::get()->createCamera(this->getEntityManager())));
        
        std::cout << " UABScoreScene initialized " << std::endl;
    }

    void v_update(const GameTime& gameTime) {
        IScene::v_update(gameTime);
    }
};

#endif