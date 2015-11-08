#ifndef _C_PHYSICS2D_H_
#define _C_PHYSICS2D_H_

#include "glm/vec2.hpp"
#include "CPT_component.h"
#include "CPT_creator.h"
#include "rapidxml\rapidxml.hpp"

class CRigidBody : public IComponent {
public:
    const static ComponentType sk_componentType;

    glm::vec2   m_velocity;
    glm::vec2   m_acceleration;
    glm::vec2   m_forceAccum;

    bool        m_bApplyGravity;

    float       m_damping;

    CRigidBody(bool applyGravity) : 
        m_velocity(glm::vec2()),
        m_acceleration(glm::vec2()),
        m_damping(0.70f), 
        m_forceAccum(glm::vec2()),
        m_bApplyGravity(applyGravity) {}

    CRigidBody(bool applyGravity, float damping) : 
        m_velocity(glm::vec2()),
        m_acceleration(glm::vec2()),
        m_damping(damping),
        m_forceAccum(glm::vec2()),
        m_bApplyGravity(applyGravity) {}

    virtual ~CRigidBody() {}

    inline const ComponentType getComponentType(void) const {
        return CRigidBody::sk_componentType;
    }

    static const char* getName(void) {
        return "CRigidBody";
    }

    void addForce(glm::vec2 forceToAdd) {
        m_forceAccum += forceToAdd;
    }

    void clearForce(void) {
        m_forceAccum.x = 0.0f;
        m_forceAccum.y = 0.0f;
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};



class CRigidBodyCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(rapidxml::xml_node<> *node) {
        CRigidBody *component = new CRigidBody(false);

        component->m_damping = 0.99f;

        if (0 == strcmp("CRigidBody", node->first_attribute("type")->value())) {
            rapidxml::xml_node<> *value;

            for (value = node->first_node("value")
                ; value
                ; value = value->next_sibling()) {

                if (0 == strcmp("applyingGravity", value->first_attribute("name")->value())) {
                    if (0 == strcmp("true", value->value())) {
                        component->m_bApplyGravity = true;
                    } else if (0 == strcmp("false", value->value())) {
                        component->m_bApplyGravity = false;
                    }
                    else {
                        assert(false);
                    }
                }
                if (0 == strcmp("damping", value->first_attribute("name")->value())) {
                    component->m_damping = atof(value->value());
                }
                else {
                    // add log
                }
            }
        }

        return component;
    }
};

#endif