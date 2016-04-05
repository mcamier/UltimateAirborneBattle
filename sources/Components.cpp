#include "components/C_missile.h"
#include "components/C_rendereable2D.h"
#include "components/C_rigidbody.h"
#include "components/C_collider.h"
#include "components/C_transform.h"
#include "components/C_plusOne.h"
#include "components/C_player.h"
#include "components/C_explosion.h"
#include "components/C_particuleEmitter.h"

#include <string>

const ComponentType CMissile::sk_componentType(0xbd69c944);
const ComponentType CTransform::sk_componentType(0x381cfbe0);
const ComponentType CRigidBody::sk_componentType(0x497e133a);
const ComponentType CCollider::sk_componentType(0x6b47e35);
const ComponentType CPlayer::sk_componentType(0xef7366f5);
const ComponentType CExplosion::sk_componentType(0x6a27a6c9);
const ComponentType CPlusOne::sk_componentType(0x5128c722);
const ComponentType CRendereable2D::sk_componentType(0x6a526657);
const ComponentType CParticuleEmitter::sk_componentType(0xcf69cb7d);