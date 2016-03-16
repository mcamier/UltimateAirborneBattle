#ifndef _P_PARTICULE_MANAGER_H_
#define _P_PARTICULE_MANAGER_H_

#include <vector>

#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_process.h"
#include "CPT_component.h"
#include "components/C_particuleEmitter.h"
#include "IParticule.h"

class PParticuleManager : public EntityUpdateProcess {
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
    const unsigned int          getID               () const;
    void                        v_before            (const GameTime& gameTime) override;
    void                        v_after             (const GameTime& gameTime) override;
    void                        v_updateEntity      (entityID id, const GameTime& gameTime) override;
    void                        v_destroy           () override;
};
#endif