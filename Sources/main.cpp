#include <iostream>
#include <assert.h>

#include "CPT_engine.h"
#include "CPT_scene.h"
#include "P_physic.h"
#include "P_player.h"
#include "P_gameManager.h"
#include "P_particuleRenderer.h"
#include "P_animationRenderer.h"
#include "P_spriteRenderer.h"
#include "P_particuleManager.h"
#include "P_collider.h"
#include "P_screenPosition.h"
#include "P_explosion.h"
#include "UAB_defines.h"

//int __frameDuration = 10;

class UABGameScene : public Scene {
public:
    UABGameScene() : Scene("GAME screen", false, true, "../Resources/inputs/inputs_game.xml") {}
    
    const unsigned int getID() const { return 10005; }

protected:
    void initialize(void) {
        assert(ActorFactory::get() != NULL);

        this->addProcess(new PGameManager());
        this->addProcess(new PExplosion());
        this->addProcess(new PPhysics2D());
        this->addProcess(new PPlayer());
        this->addProcess(new PCollider());
        this->addProcess(new PParticuleManager());
        this->addProcess(new PScreenPosition());

        this->addRenderProcess(new PAnimationRenderer());
        this->addRenderProcess(new PSpriteRenderer());

        std::cout << " UABGameScene initialized " << std::endl;
    }
};

class UltimateAirborneBattle : public CompoteEngine {

public:
    UltimateAirborneBattle() : CompoteEngine(1280, 720, 1280, 720) {}
    virtual ~UltimateAirborneBattle() {}

protected:
    void setup() {
        UABGameScene *gameScreen = new UABGameScene();
        this->pushScene(*gameScreen);
    }
};


/* Entry point
 */
int main(int, char**) {
    UltimateAirborneBattle engine;
    return engine.run();
}