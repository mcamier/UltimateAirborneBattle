#ifndef _P_PARTICULE_MANAGER_H_
#define _P_PARTICULE_MANAGER_H_

#include <vector>

#include "CPT_time.h"
#include "CPT_entity.h"
#include "CPT_process.h"
#include "CPT_component.h"
#include "C_particuleEmitter.h"

class PParticuleManager : public EntityUpdateProcess {
private:
    static const std::vector<ComponentType>     sk_requirements;

    std::list<particule_t>                      m_particulesEmitted;

public:
    PParticuleManager() :
        m_particulesEmitted(std::list<particule_t>()) {}

    virtual ~PParticuleManager() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int getID() const;
    void v_before(const GameTime& gameTime) override;
    void v_after(const GameTime& gameTime) override;
    void v_process(entityID id, const GameTime& gameTime) override;
    void v_destroy() override;
};
#endif