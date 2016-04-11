#ifndef _P_COLLISION_UTILS_H_
#define _P_COLLISION_UTILS_H_

#include <assert.h>

#include "entity/CPT_entity.h"
#include "SDL2/SDL_rect.h"
#include "components/C_transform.h"
#include "glm/vec3.hpp"

#define COLLIDER_TYPE_SPHERE_2D     1
#define COLLIDER_TYPE_SPHERE_3D     2
#define COLLIDER_TYPE_AABB_2D       3
#define COLLIDER_TYPE_AABB_3D       4
#define COLLIDER_TYPE_RAY           5


class ICollider {
public:
    virtual const int       getType         (void) = 0;
    virtual bool            isColliding     (glm::vec3 pos, ICollider *other, glm::vec3 posOther) = 0;
#ifdef _DEBUGGING
    virtual void            debugDraw       (glm::vec2 &position) = 0;
#endif
};


class CircleCollider : public ICollider {

public:
    float           m_radius;

                    CircleCollider      (float radius) : m_radius(radius) {}

    const int       getType             (void);
    bool            isColliding         (glm::vec3 pos, ICollider *other, glm::vec3 posOther);
#ifdef _DEBUGGING
    void            debugDraw           (glm::vec2 &position);
#endif

};

/*class AABBCollider : public ICollider {

public:

    AABBCollider() {}

    const int       getType(void);
    bool            isColliding(glm::vec3 &pos, ICollider *other, glm::vec3 &posOther);
#ifdef _DEBUGGING
    void            debugDraw(glm::vec2 &position);
#endif

};*/


class CollideUtils {
public:
    static bool     circleAgainstCircle (CircleCollider *o1, glm::vec3 &positionObj1, CircleCollider *o2, glm::vec3 &positionObj2);
    //static bool     aabbAgainstAabb(AABBCollider *o1, glm::vec3 &positionObj1, AABBCollider *o2, glm::vec3 &positionObj2);
};


struct collision_s {
    entityID        obj1;
    entityID        obj2;
    collision_s     *next;
};

#endif