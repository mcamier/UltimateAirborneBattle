#ifndef _UAB_GAME_SCENE_H_
#define _UAB_GAME_SCENE_H_

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

class UABGameScene : public Scene {
public:
    UABGameScene() : Scene("GAME screen", false, true, "../Resources/inputs/inputs_game.xml") {}

    const unsigned int getID() const { return 10005; }

protected:
    void initialize(void) {
        assert(ActorFactory::get() != NULL);

        this->addProcess(new PGameManager(GameMode::ONE_VS_ONE));
        this->addProcess(new PExplosion());
        this->addProcess(new PPhysics2D());
        this->addProcess(new PPlayer());
        this->addProcess(new PCollider());
        this->addProcess(new PParticuleManager());

        this->addRenderProcess(new PAnimationRenderer());
        this->addRenderProcess(new PSpriteRenderer());

        std::cout << " UABGameScene initialized " << std::endl;
    }
};

#endif