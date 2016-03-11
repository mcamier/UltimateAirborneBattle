#ifndef _UAB_SCORE_SCENE_H_
#define _UAB_SCORE_SCENE_H_

#include <assert.h>
#include "CPT_scene.h"

#include "UAB_defines.h"
#include "P_physic.h"
#include "P_player.h"
#include "P_rendereable2D.h"
#include "P_particuleManager.h"
#include "P_explosion.h"

class UABScoreScene : public Scene {
public:
    UABScoreScene() : Scene("GAME screen", false, false) {}

    int getID() const { return 10005; }

protected:
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
};

#endif