#include <iostream>
#include <tuple>
#include <functional>
#include <vector>
#include <assert.h>
#include <string>
#include <logger/loggerManager.h>
#include <logger/consoleLogger.h>

#include "core/engine.h"
#include "core/engineProperties.h"
#include "logger/loggerManager.h"
#include "utils.h"

#include "scenes/gameplayScene.h"
#include "scenes/mainMenuScene.h"
#include "scenes/titleScene.h"


#include "entity/components/C_transform.h"
#include "core/core.h"
#include "entity/components/C_collider.h"
#include "components/C_player.h"
#include "components/C_plusOne.h"
#include "entity/components/C_rigidbody.h"
#include "components/C_missile.h"
#include "entity/components/C_sprite.h"
#include "entity/components/C_animation.h"

#include "entity/actorFactory.h"


#ifdef main
# undef main
#endif /* main */

using std::string;
using namespace Compote::Core;
using namespace Compote::Entity;
using namespace Compote::Scene;


class UltimateAirborneBattle : public CompoteEngine {

public:
    GameplayScene *gameScreen;

    UltimateAirborneBattle(EngineProperties props) :
        CompoteEngine(props) {}

    virtual ~UltimateAirborneBattle() {}

protected:
    void setup() {
        Locator::getActorFactory()->addComponentFactory("CPlayer", new CPlayerFactory());
        Locator::getActorFactory()->addComponentFactory("CPlusOne", new CPlusOneFactory());
        Locator::getActorFactory()->addComponentFactory("CExplosion", new CExplosionFactory());
        Locator::getActorFactory()->addComponentFactory("CMissile", new CMissileFactory());

        TitleScene *titleScene = new TitleScene(*this);
        Locator::getSceneManager()->addScene(*titleScene);
    }
};


/* Entry point
 */
int main(int argc, char** argv) {
    EngineProperties props = EngineProperties();
    props.gameResolutionX = 1280;
    props.gameResolutionY = 720;
    props.screenResolutionX = 1280;
    props.screenResolutionY = 720;
    props.inputMappingFile = "../resources/inputs/contextMapping.xml";
    props.actorsFile = "../resources/actors.lua";
    props.resourcesFile = "../resources/resources.json";

    UltimateAirborneBattle *engine = new UltimateAirborneBattle(props);
    return engine->run();
}
