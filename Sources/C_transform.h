#ifndef _C_TRANSFORM_H
#define _C_TRANSFORM_H

#include "CPT_component.h"

#include "vec2.hpp"

class CTransform : public IComponent {
public:
    const static ComponentType sk_componentType = 0x381cfbe0;

private:
    CTransform*     m_pParent = nullptr;

    float           _x = 0;
    float           _y = 0;
    float           _scaleX = 0;
    float           _scaleY = 0;
    float           _rotation = 0;

    float           m_x;
    float           m_y;
    
    float           m_rotation;
    
    float           m_scaleX;
    float           m_scaleY;

    bool            m_dirt = true;

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

    float getX() { 
        refresh();
        return _x;
    }
    
    float getY() { 
        refresh();
        return _y;
    }

    float getScaleX(){ 
        refresh(); 
        return _scaleX;
    }
    
    float getScaleY(){ 
        refresh(); 
        return _scaleY;
    }
    
    float getRotation(){ 
        refresh();
        return _rotation; 
    }

    void setX(float x) { 
        m_x = x;
        m_dirt = true;
    }

    void setY(float y) { 
        m_y = y; 
        m_dirt = true;
    }

    void setScaleX(float scaleX) { 
        m_scaleX = scaleX; 
        m_dirt = true;
    }

    void setScaleY(float scaleY) { 
        m_scaleY = scaleY;
        m_dirt = true;
    }

    void setRotation(float rotation) { 
        m_rotation = rotation;
        m_dirt = true;
    }

    inline const ComponentType getComponentType(void) const {
        return CTransform::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CTransform";
    }

private:
    void refresh() {
        if (m_pParent != nullptr) {
            if (m_pParent->m_dirt) {
                _x = m_pParent->getX() + m_x;
                _y = m_pParent->getY() + m_y;
                _scaleX = m_pParent->getScaleX() + m_scaleX;
                _scaleY = m_pParent->getScaleY() + m_scaleY;
                _rotation = m_pParent->getRotation() + m_rotation;
                
                m_pParent->m_dirt = false;
                m_dirt = false;
            }
        }
        
        if (m_dirt) {
            _x = m_x;
            _y = m_y;
            _scaleX = m_scaleX;
            _scaleY = m_scaleY;
            _rotation = m_rotation;
            m_dirt = false;
        }
    }
};

#endif