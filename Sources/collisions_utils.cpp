#include "collisions_utils.h"

#include <stdio.h>
#include "CPT_debugRenderer.h"
#include "CPT_entityManager.h"

const int CircleCollider::getType(void) {
    return COLLIDER_TYPE_SPHERE_2D;
}

bool CircleCollider::isColliding(glm::vec3 pos, ICollider *other, glm::vec3 posOther) {
    switch (other->getType()) {

    case COLLIDER_TYPE_SPHERE_2D:
        CircleCollider *casted = static_cast<CircleCollider*>(other);
        return CollideUtils::circleAgainstCircle(this, pos, casted, posOther);
        break;
    }

    return false;
}

#ifdef _DEBUG
void CircleCollider::debugDraw(glm::vec2 &position) {
    //DebugRenderer::get()->addCircle(position, m_radius);
}
#endif


bool CollideUtils::circleAgainstCircle(CircleCollider *o1, glm::vec3 &positionObj1, CircleCollider *o2, glm::vec3 &positionObj2) {
    glm::vec2 distance = glm::vec2(.0f, .0f);
    distance.x = positionObj1.x - positionObj2.x;
    distance.y = positionObj1.y - positionObj2.y;

    if ((distance.x * distance.x) + (distance.y * distance.y) <=
        (o1->m_radius + o2->m_radius) * (o1->m_radius + o2->m_radius)) {
        return true;
    }
    return false;
}

/*
void QuadTreeNode::initialize() {
    m_pEntities = (entityID*)malloc(sizeof(entityID) * (m_amoutElementPerNode + 1));
    assert(m_pEntities != nullptr);
    for (int i = 0; i < m_amoutElementPerNode; i++) {
        m_pEntities[i] = -1;
    }
}

void QuadTreeNode::add(entityID id) {
    if (m_bLeaf){
        if (m_amountEntity <= m_amoutElementPerNode) {
            m_pEntities[m_amountEntity++] = id;

            if (m_amountEntity == m_amoutElementPerNode) {
                this->divide();
            }
        }
    }
}

void QuadTreeNode::divide() {
    if (m_bLeaf) {
        m_bLeaf = false;

        m_pNe = new QuadTreeNode(m_pEntityManager, this, m_amoutElementPerNode, m_border.x, m_border.y, m_border.w / 2, m_border.h / 2);
        m_pNe->initialize();
        m_pNw = new QuadTreeNode(m_pEntityManager, this, m_amoutElementPerNode, m_border.x + m_border.w / 2, m_border.y, m_border.w / 2, m_border.h / 2);
        m_pNw->initialize();
        m_pSe = new QuadTreeNode(m_pEntityManager, this, m_amoutElementPerNode, m_border.x, m_border.y + m_border.h / 2, m_border.w / 2, m_border.h / 2);
        m_pSe->initialize();
        m_pSw = new QuadTreeNode(m_pEntityManager, this, m_amoutElementPerNode, m_border.x + m_border.w / 2, m_border.y + m_border.h / 2, m_border.w / 2, m_border.h / 2);
        m_pSw->initialize();

        for (int i = 0; i < m_amoutElementPerNode; i++) {
            entityID id = m_pEntities[i];
            if (id >= 0) {
                CTransform* transform = m_pEntityManager.getAs<CTransform>(id);
                if (transform != nullptr) {
                    if (contains(m_pNe->m_border, transform->getX(), transform->getY()))
                        m_pNe->add(id);
                    else if (contains(m_pNw->m_border, transform->getX(), transform->getY()))
                        m_pNw->add(id);
                    else if (contains(m_pSe->m_border, transform->getX(), transform->getY()))
                        m_pSe->add(id);
                    else if (contains(m_pSw->m_border, transform->getX(), transform->getY()))
                        m_pSw->add(id);
                }
            }
        }
        free(m_pEntities);
    }
}

bool QuadTreeNode::contains(SDL_Rect& rect, float x, float y) {
    if ((x >= rect.x && x <= rect.x + rect.w) && (y >= rect.y && y <= rect.y + rect.h))
        return true;
    return false;
}*/