#ifndef _C_SCREENPOSITION_H_
#define _C_SCREENPOSITION_H_

#include "CPT_vec2f.h"
#include "CPT_component.h"

class CScreenPosition : public IComponent {
public:
    static const ComponentType sk_componentType = 0x26a4f2a0;

    Vec2f *m_pData;

    CScreenPosition(int x, int y) {
        m_pData = new Vec2f(x, y);
    }
    virtual ~CScreenPosition() {}

    inline const ComponentType getComponentType(void) const {
        return CScreenPosition::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CScreenPosition";
    }
};

#endif