#include <iostream>
#include <assert.h>

#include "CPT_engine.h"
#include "CPT_scene.h"

#include "UAB_gameScene.h"
#include "UAB_ScoreScene.h"

class UltimateAirborneBattle : public CompoteEngine {

public:
    UABGameScene *gameScreen;
    Delegate<IEvent*>   d_gameWon;

    UltimateAirborneBattle() : CompoteEngine(1280, 720, 1280, 720) {}
    virtual ~UltimateAirborneBattle() {}

protected:
    void setup() {
        d_gameWon = Delegate<IEvent*>::make<UltimateAirborneBattle, &UltimateAirborneBattle::onGameWon>(this);
        EventManager::get()->addListener(GameWonEvent::sk_EventType, d_gameWon);

        UABGameScene *gameScreen = new UABGameScene();
        this->pushScene(*gameScreen);
    }

    void onGameWon(IEvent* event) {
        //UABScoreScene *scoreScreen = new UABScoreScene();
        //this->pushScene(*scoreScreen);
    }
};


/* Entry point
 */
int main(int, char**) {
    UltimateAirborneBattle engine;
    return engine.run();
}