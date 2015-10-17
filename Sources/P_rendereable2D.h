#ifndef _P_RENDEREABLE_2D_PROCESS_H_
#define _P_RENDEREABLE_2D_PROCESS_H_


#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"

class PRendereable2D : public EntityRenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PRendereable2D() {}
    virtual ~PRendereable2D() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int  getID() const;
    void                v_renderEntity(entityID id, const GameTime& gameTime);

public:
    void                v_destroy();
};
#endif