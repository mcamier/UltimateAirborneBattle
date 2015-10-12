#include "P_collider.h"

#include "C_collider.h"
#include "C_transform.h"
#include "UAB_events.h"
#ifdef _DEBUG
#include "CPT_debugRenderer.h"
#endif

ComponentType w[] = { CCollider::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PCollider::sk_requirements(w, w + 2);

void PCollider::v_process(entityID id, const GameTime& gameTime) {
    CCollider *c1 = getEntityAs<CCollider>(id);
    CTransform *t1 = getEntityAs<CTransform>(id);

#ifdef _DEBUG
    glm::vec2 to = glm::vec2(t1->getX(), t1->getY());
    DebugRenderer::get()->addCircle(to, c1->m_radius);
#endif

    for (std::set<entityID>::iterator it = m_cache.begin()
        ; it != m_cache.end()
        ; ++it) {

        entityID obj = (*it);

        if (c1->m_bActivated){
            // don't test entity collision against itself
            if (obj != id) {
                CCollider *c2 = getEntityAs<CCollider>(obj);
                CTransform *t2 = getEntityAs<CTransform>(obj);

                glm::vec2 distance = glm::vec2(.0f, .0f);
                distance.x = t1->getX() - t2->getX();
                distance.y = t1->getY() - t2->getY();
                float length = (distance.x * distance.x) + (distance.y * distance.y);

                float val = (c1->m_radius + c2->m_radius) * (c1->m_radius + c2->m_radius);
                if (length <= val) {
                    printf("collision detected : [%f] <= [%f]\n", length, val);
                    
                    // execute collision callback
                    // add collision information to the DoubleBufferedStackAllocator

                    //(*c1->f_onCollisionCallback)(id, obj, &(getScene()));
                    /*collision_t infos;
                    infos.obj1 = id;
                    infos.obj2 = obj;*/
                }
            }
        }
    }
}

void PCollider::v_initialize(void) {
    EntityUpdateProcess::v_initialize();
    m_lastFrameCollisions->initialize();
};

void PCollider::v_destroy(void) {
    m_lastFrameCollisions->destroy();
};