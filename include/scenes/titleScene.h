#ifndef COMPOTEPLUSPLUS_TITLESCENE_H
#define COMPOTEPLUSPLUS_TITLESCENE_H

#include <vector>

#include "scene/IScene.h"
#include "logger/logger.h"
#include "scene/MenuScene.h"
#include "scene/menu/MenuItem.h"
#include "scene/sceneManager.h"
#include "event/eventManager.h"
#include "utils.h"
#include "input/inputManager.h"
#include "input/inputs.h"
#include "input/inputContextMapper.h"
#include "input/inputInterpreter.h"
#include "resource/resource.h"
#include "resource/resourceManager.h"

using std::vector;
using Compote::Core::Locator;
using namespace Compote::Scene;
using namespace Compote::Event;
using namespace Compote::Input;
using namespace Compote::Resource;


class TitleScene
        : public AbstractMenuScene {

private:
    ResHandler<SDL_Texture> *m_hTitle;
    SDL_Rect                m_titleDest;

public:
    TitleScene(CompoteEngine &engine) : AbstractMenuScene(engine) {}

    bool v_initialize(void) {
        AbstractMenuScene::v_initialize();

        m_hTitle = Locator::getResourceManager()->get<SDL_Texture>(2);
        m_titleDest.x = 200;
        m_titleDest.y = 200;
        m_titleDest.w = 512;
        m_titleDest.h = 512;
        return true;
    }


    void v_update(const GameTime& gameTime) {
        AbstractMenuScene::v_update(gameTime);
    }

    void v_handleInput(const GameTime& gameTime) override {
        gameInput_t *input;
        while((input = Locator::getInput()->pollInput()) != nullptr) {
            switch(input->ID) {

                case MENU_INPUT_SELECT:
                    MainMenuScene *mainMenu = new MainMenuScene(this->m_engine);
                    Locator::getSceneManager()->addScene(*mainMenu);
                    break;
            }
        }
    }

    void v_render(const GameTime& gameTime) {
        Locator::getRenderer()->renderTexture(m_hTitle->get(), &m_titleDest, getTransitionRange());
        Locator::getRenderer()->renderText("PRESS START", 500, 500);
    }

    void v_destroy(void) {

    }

};
#endif //COMPOTEPLUSPLUS_TITLESCENE_H
