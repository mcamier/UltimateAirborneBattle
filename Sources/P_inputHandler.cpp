#include "P_inputHandler.h"

#include "C_playerInputHandler.h"

ComponentType y[] = { CInputHandler::sk_componentType };
const std::vector<ComponentType> PInputHandler::sk_requirements(y, y +1);

void PInputHandler::v_destroy() {
}

void PInputHandler::v_process(entityID id, const GameTime& gameTime) {
    CInputHandler* input = getEntityAs<CInputHandler>(id);

    input->putain();
}