#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include "glm/vec2.hpp"
#include "CPT_component.h"
#include "CPT_creator.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class CPlayer : public IComponent {
public:
    const static ComponentType sk_componentType;

public:
    glm::vec2           m_forward;

    float               m_actualThrustAmount = 0.0f;
    float               m_maxThrustAmount = 300.0f;
    float               m_speedupThrustAmount = 450.0f;

    float               m_elapsedTime = 0;
    float               m_floatingAmount;
    const float         m_defaultCooldown = 1500.0f;
    float               m_cooldown = 0.0f;
    bool                m_bAlive;
    bool                m_bSpeedUp;
    

    CPlayer() : 
        m_floatingAmount(0), 
        m_forward(glm::vec2(1.0f, .0f)),
        m_bAlive(true),
        m_bSpeedUp(false) {}

    CPlayer(glm::vec2 forward) :
        m_floatingAmount(0), 
        m_forward(forward), 
        m_bAlive(true),
        m_bSpeedUp(false) {}

    virtual ~CPlayer() {}

    inline const ComponentType getComponentType(void) const {
        return CPlayer::sk_componentType;
    }

    static const char* getName(void) {
        return "CPlayer";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};


class CPlayerCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(const rapidjson::Value& node) {
        CPlayer *component = new CPlayer();

        component->m_forward.x = 1.0f;
        component->m_forward.y = 1.0f;

        /*if (0 == strcmp("CPlayer", node->first_attribute("class")->value())) {
            rapidxml::xml_node<> *value;

            for (value = node->first_node("value")
                ; value
                ; value = value->next_sibling()) {

                if (0 == strcmp("forward", value->first_attribute("name")->value())) {
                    rapidxml::xml_node<> *x = value->first_node();
                    
                    component->m_forward.x = atof(x->value());
                    component->m_forward.y = atof(x->next_sibling()->value());
                }
                else {
                    // add log
                }
            }
        }*/

        return component;
    }
};

#endif