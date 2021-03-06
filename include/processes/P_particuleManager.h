#ifndef _P_PARTICULE_MANAGER_H_
#define _P_PARTICULE_MANAGER_H_

#include <vector>

#include "core/core.h"
#include "entity/entity.h"
#include "process.h"
#include "entity/component.h"
#include "entity/components/C_particuleEmitter.h"
#include "graphic/particule/particule.h"

using Compote::Core::GameTime;
using namespace Compote::Graphic::Particule;

class PParticuleManager : public UpdateProcess {
private:
    static const std::vector<ComponentType>     sk_requirements;
    std::list<IParticule*>                      m_particulesEmitted;

public:
    PParticuleManager() :
        m_particulesEmitted(std::list<IParticule*>()) {}

    virtual ~PParticuleManager() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    void                        v_before            (const GameTime& gameTime) override;
    void                        v_after             (const GameTime& gameTime) override;
    void                        v_updateEntity      (entityID id, const GameTime& gameTime) override;
    void                        v_destroy           () override;
};
#endif