#ifndef _P_COLLISION_UTILS_H_
#define _P_COLLISION_UTILS_H_

#include <assert.h>

#include "CPT_entity.h"
#include "SDL_rect.h"
#include "C_transform.h"
#include "vec3.hpp"

#define COLLIDER_TYPE_SPHERE_2D     1
#define COLLIDER_TYPE_SPHERE_3D     2
#define COLLIDER_TYPE_AABB_2D       3
#define COLLIDER_TYPE_AABB_3D       4
#define COLLIDER_TYPE_RAY           5


class ICollider {
public:
    virtual const int       getType         (void) = 0;
    virtual bool            isColliding     (glm::vec3 &pos, ICollider *other, glm::vec3 &posOther) = 0;
#ifdef _DEBUG
    virtual void            debugDraw       (glm::vec2 &position) = 0;
#endif
};


class CircleCollider : public ICollider {

public:
    float           m_radius;

                    CircleCollider      (float radius) : m_radius(radius) {}

    const int       getType             (void);
    bool            isColliding         (glm::vec3 &pos, ICollider *other, glm::vec3 &posOther);
#ifdef _DEBUG
    void            debugDraw           (glm::vec2 &position);
#endif

};

/*class AABBCollider : public ICollider {

public:

    AABBCollider() {}

    const int       getType(void);
    bool            isColliding(glm::vec3 &pos, ICollider *other, glm::vec3 &posOther);
#ifdef _DEBUG
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

/*
class QuadTreeNode {
private:
    QuadTreeNode        *m_pParent;

    QuadTreeNode        *m_pNe;
    QuadTreeNode        *m_pNw;
    QuadTreeNode        *m_pSe;
    QuadTreeNode        *m_pSw;

    SDL_Rect            m_border;
    const int           m_amoutElementPerNode;
    int                 m_amountEntity = 0;
    entityID            *m_pEntities;
    bool                m_bLeaf = true;
    EntityManager       &m_pEntityManager;

public:
    QuadTreeNode(EntityManager &entityManager, QuadTreeNode *parent, int amoutElementPerNode, float x, float y, float w, float h) :
        m_pEntityManager(entityManager),
        m_pParent(parent),
        m_amoutElementPerNode(amoutElementPerNode),
        m_pNe(nullptr),
        m_pNw(nullptr),
        m_pSe(nullptr),
        m_pSw(nullptr),
        m_border(SDL_Rect()) {

        m_border.x = x;
        m_border.y = y;
        m_border.w = w;
        m_border.h = h;
    }

private:
    QuadTreeNode(const QuadTreeNode& other) : 
        m_amoutElementPerNode(other.m_amoutElementPerNode), 
        m_pEntityManager(other.m_pEntityManager) {};
    const QuadTreeNode& operator=(const QuadTreeNode&) {};

    void initialize();
    void add(entityID id);
    void divide();

private:
    static bool contains(SDL_Rect& rect, float x, float y);
};
*/
#endif