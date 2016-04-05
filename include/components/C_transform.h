#ifndef _C_TRANSFORM_H
#define _C_TRANSFORM_H

#include "entity/CPT_component.h"

#include "glm/vec2.hpp"
#include "entity/CPT_creator.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class CTransform : public IComponent {
public:
    const static ComponentType sk_componentType;

private:
    CTransform*     m_pParent = nullptr;

    float           m_x = 0.0f;
    float           m_y = 0.0f;
    float           m_offsetX = 0.0f;
    float           m_offsetY = 0.0f;

    float           m_rotation;
    
    float           m_scaleX;
    float           m_scaleY;

    float           __x = 0.0f;
    float           __y = 0.0f;
    float           __scaleX = 0.0f;
    float           __scaleY = 0.0f;
    float           __rotation = 0.0f;

    bool            m_bDirt = true;

public:

    CTransform() :
        m_scaleX(1), m_scaleY(1),
        m_x(0), m_y(0),
        m_rotation(.0f) {}

    CTransform(int x, int y) :
        m_rotation(.0f),
        m_scaleX(1), m_scaleY(1),
        m_x(x), m_y(y) {}

    CTransform(int x, int y, float rotation) :
        m_rotation(rotation),
        m_scaleX(1), m_scaleY(1),
        m_x(x), m_y(y) {}

    CTransform(int x, int y, float rotation, glm::vec2 scale) :
        m_rotation(rotation),
        m_scaleX(scale.x), m_scaleY(scale.y),
        m_x(x), m_y(y) {}


    CTransform(CTransform* pParent) :
        m_pParent(pParent),
        m_scaleX(1), m_scaleY(1),
        m_x(0), m_y(0),
        m_rotation(.0f) {}

    CTransform(CTransform* pParent, int x, int y) :
        m_pParent(pParent),
        m_rotation(.0f),
        m_scaleX(1), m_scaleY(1),
        m_x(x), m_y(y) {}

    CTransform(CTransform* pParent, int x, int y, float rotation) :
        m_pParent(pParent),
        m_rotation(rotation),
        m_scaleX(1), m_scaleY(1),
        m_x(x), m_y(y) {}

    CTransform(CTransform* pParent, int x, int y, float rotation, glm::vec2 scale) :
        m_pParent(pParent),
        m_rotation(rotation),
        m_scaleX(scale.x), m_scaleY(scale.y),
        m_x(x), m_y(y) {}

    virtual ~CTransform() {}


    /* get inner values (in world values) */
    float getTransformX() {
        refresh();
        return __x;
    }

    float getTransformY() {
        refresh();
        return __y;
    }
    float getTransformScaleX() {
        refresh();
        return __scaleX;
    }
    float getTransformScaleY() {
        refresh();
        return __scaleY;
    }
    float getTransformRotation() {
        refresh();
        return __rotation;
    }



    float getX() {
        return m_x;
    }

    float getY() {
        return m_y;
    }

    float getOffsetX() {
        return m_offsetX;
    }

    float getOffsetY() {
        return m_offsetY;
    }

    float getScaleX(){  
        return m_scaleX;
    }
    
    float getScaleY(){ 
        return m_scaleY;
    }
    
    float getRotation() { 
        return m_rotation; 
    }


    void setX(float x) {
        m_x = x;
        m_bDirt = true;
    }

    void setY(float y) {
        m_y = y;
        m_bDirt = true;
    }

    void setOffsetX(float x) {
        m_offsetX = x;
        m_bDirt = true;
    }

    void setOffsetY(float y) {
        m_offsetY = y;
        m_bDirt = true;
    }

    void setScaleX(float scaleX) { 
        m_scaleX = scaleX; 
        m_bDirt = true;
    }

    void setScaleY(float scaleY) { 
        m_scaleY = scaleY;
        m_bDirt = true;
    }

    void setRotation(float rotation) { 
        m_rotation = rotation;
        m_bDirt = true;
    }

    IComponent* clone(void) const {
        CTransform *clone = new CTransform();
        clone->m_bDirt = true;
        clone->m_x = this->m_x;
        clone->m_y = this->m_y;
        clone->m_offsetX = this->m_offsetX;
        clone->m_offsetY = this->m_offsetY;
        clone->m_scaleX = this->m_scaleX;
        clone->m_scaleY = this->m_scaleY;
        clone->m_rotation = this->m_rotation;
        clone->m_pParent = this->m_pParent;
        return clone;
    }

    inline const ComponentType getComponentType(void) const {
        return CTransform::sk_componentType;
    }

    static const char* getName(void) {
        return "CTransform";
    }

private:
    void refresh() {
        if (m_pParent != nullptr) { 
            if (m_pParent->m_bDirt){
                __x = m_pParent->getTransformX() + m_x + m_offsetX;
                __y = m_pParent->getTransformY() + m_y + m_offsetY;
                __scaleX = m_pParent->getTransformScaleX() * m_scaleX;
                __scaleY = m_pParent->getTransformScaleY() * m_scaleY;
                __rotation = m_pParent->getTransformRotation() + m_rotation;
            }
        }
        else{
            if (m_bDirt) {
                __x = m_x + m_offsetX;
                __y = m_y + m_offsetY;
                __scaleX = m_scaleX;
                __scaleY = m_scaleY;
                __rotation = m_rotation;
            }
        }
        m_bDirt = false;
    }
};


class CTransformCreator : 
    public BaseCreator<IComponent> {

public:
    IComponent* create(const rapidjson::Value& node) {
        CTransform *component = new CTransform();

        component->setX(0.0f);
        component->setY(0.0f);
        component->setScaleX(0.0f);
        component->setScaleY(0.0f);
        component->setOffsetX(0.0f);
        component->setOffsetY(0.0f);

        if (node.HasMember("x")) {
            component->setX(node["x"].GetInt());
        }
        if (node.HasMember("x")) {
            component->setX(node["x"].GetInt());
        }
        if (node.HasMember("scaleX")) {
            component->setX(node["scaleX"].GetInt());
        }
        if (node.HasMember("scaleY")) {
            component->setX(node["scaleY"].GetInt());
        }
        if (node.HasMember("offsetX")) {
            component->setX(node["offsetX"].GetInt());
        }
        if (node.HasMember("offsetY")) {
            component->setX(node["offsetY"].GetInt());
        }
        if (node.HasMember("rotation")) {
            component->setX(node["rotation"].GetInt());
        }

        return component;
    }
};

#endif