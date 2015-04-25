#pragma once
#include "common.h"

class ShootingCollider : public GameLayer {

	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Rect, m_collider, Collider);

	ShootingCollider();
	virtual ~ShootingCollider();

	virtual cocos2d::Rect getColliderPosition() const;
	virtual bool isHit(const ShootingCollider *pCollision) const;

};
