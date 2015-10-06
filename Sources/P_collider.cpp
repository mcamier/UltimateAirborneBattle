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
    glm::vec2 to = glm::vec2();
    DebugRenderer::get()->addCircle(t1->m_position, c1->m_radius);
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
                distance = t1->m_position - t2->m_position;

                /* WRONG
                if (distance.length() < sqrtf((c1->m_radius + c2->m_radius) * (c1->m_radius + c2->m_radius))) {
                    (*c1->f_onCollisionCallback)(id, obj, &(getScene()));
                }*/
            }
        }
    }
}