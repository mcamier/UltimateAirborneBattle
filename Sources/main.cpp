#include <iostream>
#include <assert.h>

#include "CPT_engine.h"
#include "CPT_scene.h"

#include "UAB_gameScene.h"
#include "UAB_scoreScene.h"

#include "CPT_utils.h"
#include <string>

class UltimateAirborneBattle : public CompoteEngine {

public:
    UABGameScene *gameScreen;
    Delegate<IEvent*>   d_gameWon;
    //Delegate<IEvent*>   d_resetRequested;

    UltimateAirborneBattle() : CompoteEngine(1280, 720, 1280, 720, "../Resources/inputs/contextMapping.xml") {}
    virtual ~UltimateAirborneBattle() {}

protected:
    void setup() {
        d_gameWon = Delegate<IEvent*>::make<UltimateAirborneBattle, &UltimateAirborneBattle::onGameWon>(this);
        EventManager::get()->addListener(GameWonEvent::sk_EventType, d_gameWon);

        /*d_resetRequested = Delegate<IEvent*>::make<UltimateAirborneBattle, &UltimateAirborneBattle::onResetGame>(this);
        EventManager::get()->addListener(InputEvent::sk_EventType, d_resetRequested);*/

        UABGameScene *gameScreen = new UABGameScene();
        this->pushScene(*gameScreen);
    }

    void onGameWon(IEvent* event) {
        //UABScoreScene *scoreScreen = new UABScoreScene();
        //this->pushScene(*scoreScreen);
    }
    /*
    void onResetGame(IEvent *eventData) {
        InputEvent *e = static_cast<InputEvent*>(eventData);

        if (e->m_eventID == INPUT_RESET_EVENT) {
            printf("reset game\n");
            // by pushing new scene the old one will be deleted
            gameScreen = new UABGameScene();
            this->pushScene(*gameScreen);
        }
    }
    */
};

/* Entry point
 */
int main(int, char**) {
    UltimateAirborneBattle engine;
    return engine.run();
}