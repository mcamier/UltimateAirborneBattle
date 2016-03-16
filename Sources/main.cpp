#include <iostream>
#include <assert.h>
#include <string>

#include "CPT_engine.h"
#include "CPT_scene.h"
#include "CPT_utils.h"
#include "CPT_event.h"
#include "CPT_locator.h"

#include "UAB_gameScene.h"
#include "UAB_scoreScene.h"

#include "CPT_creator.h"

#include "components/C_transform.h"
#include "CPT_actorFactory.h"
#include "CPT_locator.h"
#include "components/C_collider.h"
#include "components/C_player.h"
#include "components/C_plusOne.h"
#include "components/C_rigidbody.h"
#include "components/C_missile.h"
#include "components/C_sprite.h"
#include "components/C_animation.h"

#ifdef main
# undef main
#endif /* main */

class UltimateAirborneBattle : public CompoteEngine {

public:
    UABGameScene *gameScreen;

    UltimateAirborneBattle() : 
        CompoteEngine(1280, 720, 1280, 720, 
        "../Resources/inputs/contextMapping.xml", 
        "../Resources/actors.json", 
        "../Resources/resources.json") {}

    virtual ~UltimateAirborneBattle() {}

protected:
    void setup() {
        Locator::getActorFactory()->addCreator<CTransform>(new CTransformCreator());
        Locator::getActorFactory()->addCreator<CPlayer>(new CPlayerCreator());
        Locator::getActorFactory()->addCreator<CPlusOne>(new CPlusOneCreator());
        Locator::getActorFactory()->addCreator<CExplosion>(new CExplosionCreator());
        Locator::getActorFactory()->addCreator<CMissile>(new CMissileCreator());
        Locator::getActorFactory()->addCreator<CRigidBody>(new CRigidBodyCreator());
        Locator::getActorFactory()->addCreator<CSprite>(new CSpriteCreator());
        //Locator::getActorFactory()->addCreator<CAnimation>(new CAnimationCreator());
        //Locator::getActorFactory()->addCreator<CParticulEmitter>(new CParticulEmitterCreator());
        //Locator::getActorFactory()->addCreator<CCollider>(new CColliderCreator());


        UABScoreScene *scoreScene = new UABScoreScene();
        UABGameScene *gameScreen = new UABGameScene();
        this->pushScene(*gameScreen);
        this->pushScene(*scoreScene);
    }
};


/* Entry point
 */
int main(int argc, char** argv) {
    UltimateAirborneBattle engine;
    return engine.run();
}