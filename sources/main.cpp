#include <iostream>
#include <assert.h>
#include <string>

#include "core/engine.h"
#include "CPT_utils.h"
#include "CPT_event.h"

#include "scenes/UAB_gameScene.h"
#include "scenes/UAB_scoreScene.h"

#include "entity/CPT_creator.h"

#include "components/C_transform.h"
#include "entity/CPT_actorFactory.h"
#include "core/core.h"
#include "components/C_collider.h"
#include "components/C_player.h"
#include "components/C_plusOne.h"
#include "components/C_rigidbody.h"
#include "components/C_missile.h"
#include "components/C_sprite.h"
#include "components/C_animation.h"

extern "C" {
#include "lua5.3/lua.h"
#include "lua5.3/lualib.h"
#include "lua5.3/lauxlib.h"
}

#ifdef main
# undef main
#endif /* main */

using Compote::Core::CompoteEngine;
using Compote::Core::Locator;

class UltimateAirborneBattle : public CompoteEngine {

public:
    UABGameScene *gameScreen;

    UltimateAirborneBattle() : 
        CompoteEngine(1280, 720, 1280, 720, 
        "../resources/inputs/contextMapping.xml",
        "../resources/actors.json",
        "../resources/resources.json") {}

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

        UABGameScene *gameScreen = new UABGameScene();
        //AbstractMenuScene *mainMenu = new AbstractMenuScene();
        this->pushScene(*gameScreen);
        //this->pushScene(*mainMenu);
    }
};


/* Entry point
 */
int main(int argc, char** argv) {
    UltimateAirborneBattle engine;
    return engine.run();
}