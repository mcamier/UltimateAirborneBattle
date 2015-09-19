#ifndef _C_INPUT_HANDLER_H_
#define _C_INPUT_HANDLER_H_

#include "CPT_component.h"

class CInputHandler : public IComponent {

public:
    const static ComponentType sk_componentType = 0x72187b3c;

    CInputHandler(){}
    virtual ~CInputHandler() {}

    inline const ComponentType getComponentType(void) const {
        return CInputHandler::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CInputHandler";
    }

    virtual void putain() = 0;

};


#endif