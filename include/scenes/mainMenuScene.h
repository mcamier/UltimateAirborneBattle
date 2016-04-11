#ifndef COMPOTEPLUSPLUS_MAINMENUSCENE_H
#define COMPOTEPLUSPLUS_MAINMENUSCENE_H

#include <vector>

#include "scene/IScene.h"
#include "logger/logger.h"
#include "scene/MenuScene.h"
#include "scene/menu/MenuItem.h"
#include "event/eventManager.h"
#include "utils.h"
#include "input/inputManager.h"
#include "input/inputs.h"
#include "input/inputContextMapper.h"
#include "input/inputInterpreter.h"

using std::vector;
using Compote::Core::Locator;
using namespace Compote::Scene;
using namespace Compote::Event;
using namespace Compote::Input;


class MainMenuScene
        : public AbstractMenuScene {

    typedef vector<MenuItem*> MenuItems;

private:
    vector<MenuItem*> m_menuItems;
    int m_amountItem;
    int m_currentItemIndex;

public:
    bool v_initialize(void) {
        AbstractMenuScene::v_initialize();

        m_menuItems = MenuItems();
        m_menuItems.push_back(new MenuItem("Play"));
        m_menuItems.push_back(new MenuItem("Options"));

        MenuItem *quitButton = new MenuItem("Quit");
        quitButton->setClickCallback(UICallback::make<MainMenuScene, &MainMenuScene::onQuitClicked>(this));
        m_menuItems.push_back(quitButton);

        m_amountItem = 3;
        m_currentItemIndex = 0;

        // initialize all the menu items
        int i = 0;
        SDL_Rect rect = Locator::getRenderer()->getGameResolution();

        for(MenuItems::iterator it = m_menuItems.begin()
                ;it != m_menuItems.end()
                ;++it) {
            (*it)->v_initialize();
            (*it)->setX(rect.w/2 - (*it)->getWidth()/2);
            (*it)->setY(rect.h/2 + (i++ *50));
        }

        m_menuItems.at(m_currentItemIndex)->setActive(true);

        return true;
    }

    void v_update(const GameTime& gameTime) {
        AbstractMenuScene::v_update(gameTime);

        gameInput_t *input;
        while((input = Locator::getInput()->pollInput()) != nullptr) {
            switch(input->ID) {
                case MENU_INPUT_NEXT:
                    m_menuItems.at(m_currentItemIndex)->setActive(false);
                    m_currentItemIndex++;
                    if(m_currentItemIndex>=m_amountItem) m_currentItemIndex = 0 ;
                    m_menuItems.at(m_currentItemIndex)->setActive(true);
                    break;

                case MENU_INPUT_PREVIOUS:
                    m_menuItems.at(m_currentItemIndex)->setActive(false);
                    m_currentItemIndex--;
                    if(m_currentItemIndex<0) m_currentItemIndex = m_amountItem -1;
                    m_menuItems.at(m_currentItemIndex)->setActive(true);
                    break;

                case MENU_INPUT_SELECT:
                    m_menuItems.at(m_currentItemIndex)->click();
                    break;

                case MENU_INPUT_ECHAP:
                    onQuitClicked();
                    break;

                case MENU_MOUSE_MOTION: {
                    int index = 0;
                    for (auto it = m_menuItems.begin(); it != m_menuItems.end(); ++it) {
                        if ((*it)->testCollision(input->payload.motion.x, input->payload.motion.y)) {
                            m_menuItems.at(m_currentItemIndex)->setActive(false);
                            (*it)->setActive(true);
                            m_currentItemIndex = index;
                            break;
                        }
                        index++;
                    }
                    break;
                }

                case MENU_MOUSE_CLICK:
                    for(auto it = m_menuItems.begin(); it != m_menuItems.end(); ++it) {
                        if( (*it)->testCollision(input->payload.motion.x, input->payload.motion.y) ) {
                            (*it)->click();
                            break;
                        }
                    }
                    break;
            }
        }
    }

    void v_render(const GameTime& gameTime) {
        for(auto it = m_menuItems.begin(); it != m_menuItems.end(); ++it) {
            (*it)->v_render(gameTime);
        }
    }

    void v_destroy(void) {
        for(auto it = m_menuItems.begin(); it != m_menuItems.end(); ++it) {
            (*it)->v_destroy();
        }
    }

    void onPlayClicked(void) {}

    void onOptionsClicked(void) {}

    void onQuitClicked(void) {
        _DEBUG("QUIT THE GAME");
        Locator::getEventManager()->fireEvent(new ShutdownEvent());
    }

};

#endif //COMPOTEPLUSPLUS_MAINMENUSCENE_H
