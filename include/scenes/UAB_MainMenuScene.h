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

class UABMainMenuScene : public IScene {
public:
    UABMainMenuScene() : IScene("Main menu", false, false) {}

public:
    void initialize(void) {
        std::cout << " UABMainMenu initialized " << std::endl;
    }

    bool v_initialize(void) {

    }

    void v_update(const GameTime& gameTime) {
        //do update here
    }

    void v_render(const GameTime& gameTime) {
        //do rendering here
    }

    void v_destroy(void) {

    }
};

#endif