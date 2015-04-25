#include "ShootingCollider.h"

USING_NS_CC;

ShootingCollider::ShootingCollider()
{
}

ShootingCollider::~ShootingCollider()
{
}

Rect ShootingCollider::getColliderPosition() const
{
	Rect collider = m_collider;
	collider.origin += this->getPosition();
	return collider;
}

bool ShootingCollider::isHit(const ShootingCollider *pCollision) const
{
	return this->getColliderPosition().intersectsRect(pCollision->getColliderPosition());
}
