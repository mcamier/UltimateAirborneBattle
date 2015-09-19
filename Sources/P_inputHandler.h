#ifndef _P_INPUT_HANDLER_H_
#define _P_INPUT_HANDLER_H_

#include "CPT_process.h"

#include "C_inputHandler.h"

class PInputHandler : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PInputHandler() {};

    const unsigned int getID() const { return 100013; }

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void v_process(entityID id, const GameTime& gameTime);
    void v_destroy(void);
};

#endif