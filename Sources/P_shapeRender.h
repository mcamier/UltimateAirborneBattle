#ifndef _UAB_P_SHAPE_RENDER_H_
#define _UAB_P_SHAPE_RENDER_H_

#include <vector>

#include "CPT_process.h"

class PShapeRender : public EntityRenderProcess {
private:
    static const std::vector<ComponentType> sk_requirements;

public:
    PShapeRender() {}
    ~PShapeRender() {}

    inline const unsigned int getID() const { return 10004; }
    
    const std::vector<ComponentType> getRequirements() const {
        return sk_requirements;
    }

    void v_destroy(void) {};
private:

    void v_processRender(entityID id, const GameTime& gameTime);
};

#endif