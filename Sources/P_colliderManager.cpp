#include "P_colliderManager.h"
#include "C_collider.h"
#include "UAB_events.h"
#include "CPT_debugRenderer.h"

ComponentType w[] = { CCollider::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PColliderManager::sk_requirements(w, w + 2);

void PColliderManager::v_initialize(void) {
    UpdateProcess::v_initialize();
    this->m_pDetectedCollisions->initialize();
    this->m_pHeadCurrentCollisions = nullptr;
    this->m_pHeadOldCollisions = nullptr;
}


void PColliderManager::v_before(const GameTime& gameTime) {
    std::set<entityID>::const_iterator iter1, iter2;
    CCollider *c1, *c2;
    CTransform *t1, *t2;

    for (iter1 = m_cache.begin()
        ;iter1 != m_cache.end()
        ;iter1++) {

        iter2 = iter1;
        iter2++;
        c1 = getEntityAs<CCollider>((*iter1));
        t1 = getEntityAs<CTransform>((*iter1));
        
/*#ifdef _DEBUG
        c1->m_collider->debugDraw(glm::vec2(t1->getX(), t1->getY()));  
#endif*/

        if (iter2 != m_cache.end()) {
            for (
                ; iter2 != m_cache.end()
                ; iter2++) {

                c2 = getEntityAs<CCollider>((*iter2));
                t2 = getEntityAs<CTransform>((*iter2));
         
                if (c1->m_bActivated && c2->m_bActivated) {                                     // only test if both collider are activated
                    bool isColliding = c1->m_collider->isColliding(
                        glm::vec3(t1->getX(), t1->getY(), 0),                                   // position of the tested object
                        c2->m_collider,                                                         // other object's collider
                        glm::vec3(t2->getX(), t2->getY(), 0)                                    // other object's position
                        );

                    if (isColliding) {
                        this->addCollision((*iter1), (*iter2));                                       // remains this collision
                        bool collideLastFrame = this->collisionOccuredLastFrame((*iter1), (*iter2));  // looks if collision between this objects occurs last frame


                        if (c1->m_bActivated && c1->f_onCollisionCallback != nullptr) {
                            if ((c1->m_callbackOncePerContact && !collideLastFrame) || !c1->m_callbackOncePerContact) {
                                (*c1->f_onCollisionCallback) ((*iter1), (*iter2), &(getScene()));
                            }
                        }
                        // take care of c2 callback because once c1 against c2 is tested the algorithm will not
                        // test c2 against c1
                        if (c2->m_bActivated && c2->f_onCollisionCallback != nullptr) {
                            if ((c2->m_callbackOncePerContact && !collideLastFrame) || !c1->m_callbackOncePerContact) {
                                (*c2->f_onCollisionCallback) ((*iter2), (*iter1), &(getScene()));
                            }
                        }
                    }
                }
            }
        }
        else {
            break;
        }
    }


    m_pHeadOldCollisions = m_pHeadCurrentCollisions;
    m_pHeadCurrentCollisions = nullptr;

    this->m_pDetectedCollisions->swapBuffer();
    this->m_pDetectedCollisions->clear();
}

void PColliderManager::addCollision(entityID id1, entityID id2) {
    collision_s *collision = m_pDetectedCollisions->alloc<collision_s>();
    assert(collision != nullptr);
    collision->obj1 = id1;
    collision->obj2 = id2;
    collision->next = nullptr;
    if (nullptr == this->m_pHeadCurrentCollisions) {
        this->m_pHeadCurrentCollisions = collision;
    }
    else {
        collision->next = this->m_pHeadCurrentCollisions;
        this->m_pHeadCurrentCollisions = collision;
    }
}


bool PColliderManager::collisionOccuredLastFrame(entityID id1, entityID id2) {
    collision_s *col = m_pHeadOldCollisions;
    while (col != nullptr) {
        if ((col->obj1 == id1 && col->obj2 == id2) || (col->obj2 == id1 && col->obj1 == id2))
            return true;
        col = col->next;
    }
    return false;
}


void PColliderManager::v_destroy() {
    m_pDetectedCollisions->destroy();
}