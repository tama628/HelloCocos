#include "ShootingBullet.h"

USING_NS_CC;

ShootingBullet *ShootingBullet::create( const Description &description )
{
	auto *pBullet = ShootingBullet::create();
	pBullet->m_description = description;
	return pBullet;
}

ShootingBullet::ShootingBullet()
{
}

ShootingBullet::~ShootingBullet()
{
}

void ShootingBullet::initialize()
{
	auto *pSprite = DrawNode::create();
	pSprite->drawDot( Vec2::ZERO, m_description.size, m_description.color );
	this->addChild( pSprite );

	this->setCollider(Rect(-m_description.size, -m_description.size, m_description.size, m_description.size));
}

void ShootingBullet::finalize()
{
}

void ShootingBullet::enter()
{
}

void ShootingBullet::leave()
{
}

bool ShootingBullet::input()
{
	return false;
}

void ShootingBullet::process(float delta)
{
	auto nextPosition = this->getPosition() + m_description.addPosition;
	this->setPosition( nextPosition );
}

ShootingBulletManager::ShootingBulletManager()
{
}

ShootingBulletManager::~ShootingBulletManager()
{
}

void ShootingBulletManager::initialize()
{
}

void ShootingBulletManager::finalize()
{
}

void ShootingBulletManager::enter()
{
}

void ShootingBulletManager::leave()
{
}

bool ShootingBulletManager::input()
{
	return false;
}

void ShootingBulletManager::process(float delta)
{
}

void ShootingBulletManager::lateProcess(float delta)
{
	// 画面外の弾を削除する
	auto &children = this->getChildren();
	for( int i = 0; i < children.size(); i++ )
	{
		auto *pNode = children.at(i);
		auto position = GameUtility::localToWorldPosition(pNode);
		if( !GameUtility::isHit( position.x, position.y, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT ) )
		{
			this->removeChild( pNode );
			i--;
		}
	}
}

void ShootingBulletManager::addChild( ShootingBullet *pBullet )
{
	super::addChild( pBullet );
}
