#include <iostream>

#include "CPT_engine.h"
#include "CPT_scene.h"
#include "P_physic.h"
#include "P_player.h"
#include "P_gameManager.h"
#include "P_particuleRenderer.h"
#include "P_animationRenderer.h"
#include "P_spriteRenderer.h"
#include "P_particuleEmitter.h"
#include "P_collider.h"
#include "P_screenPosition.h"

int __frameDuration = 10;

class UABGameScene : public Scene {
public:
    UABGameScene() : Scene("GAME screen", false, true) {}
    
    const unsigned int getID() const { return 10005; }

protected:
    void initialize(void) {
        std::cout << " UABGameScene initialized " << std::endl;

        this->addRenderProcess(new PParticuleRenderer());
        this->addRenderProcess(new PSpriteRenderer());
        this->addRenderProcess(new PAnimationRenderer());

        this->addProcess(new PPhysics2D());
        this->addProcess(new PPlayer());
        this->addProcess(new PCollider());
        this->addProcess(new PGameManager());
        this->addProcess(new PParticuleEmitter());
        this->addProcess(new PScreenPosition());


        // refactor to have only one 2DRenderer process
        // One unique renderer Component, and each PParticule, 
        // PSprite, PAnimation while update this unique 2DRenderer's state
        
    }
};

class UltimateAirborneBattle : public CompoteEngine {

public:
    UltimateAirborneBattle() : CompoteEngine(640,360,1280,720) {}
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