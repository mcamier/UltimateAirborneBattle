#ifndef _P_RENDEREABLE_2D_PROCESS_H_
#define _P_RENDEREABLE_2D_PROCESS_H_

#include "CPT_process.h"
#include "CPT_time.h"
#include "CPT_entity.h"

#include "glm/vec2.hpp"

class PRendereable2D : public EntityRenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

    entityID m_cameraID;
    glm::vec2 m_cameraPositionThisFrame;

public:
    PRendereable2D(entityID cameraID) : 
        m_cameraID(cameraID),
        m_cameraPositionThisFrame(glm::vec2(0,0)){}

    virtual ~PRendereable2D() {}

    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

private:
    const unsigned int  getID() const;
    void                v_before(const GameTime& gameTime);
    void                v_renderEntity(entityID id, const GameTime& gameTime);

public:
    void                v_destroy();
};
#endif