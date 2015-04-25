#include "ShootingEnemy.h"

USING_NS_CC;

ShootingEnemy *ShootingEnemy::create(const Description &description)
{
	auto *pInstance = ShootingEnemy::create();
	pInstance->m_description = description;
	return pInstance;
}

ShootingEnemy::ShootingEnemy()
{
}

ShootingEnemy::~ShootingEnemy()
{
}

void ShootingEnemy::initialize()
{
	const int VERTEX_MAX = 4;
	const Size SIZE = { 16, 16 };
	const Size SIZE_HALF = SIZE/2;
	const Vec2 VERTEX_ARRAY[ VERTEX_MAX ] = {
		{ -SIZE_HALF.width, -SIZE_HALF.height },
		{ -SIZE_HALF.width, SIZE_HALF.height },
		{ SIZE_HALF.width, SIZE_HALF.height },
		{ SIZE_HALF.width, -SIZE_HALF.height }
	};

	auto *pSprite = DrawNode::create();
	pSprite->drawPolygon( VERTEX_ARRAY, VERTEX_MAX, Color4F(1,1,1,0), 1, Color4F(1,0,0,1) );
	this->addChild( pSprite );

	this->setCollider(Rect(-SIZE_HALF.width, -SIZE_HALF.height, SIZE.width, SIZE.height));
}

void ShootingEnemy::finalize()
{
}

void ShootingEnemy::enter()
{
}

void ShootingEnemy::leave()
{
}

bool ShootingEnemy::input()
{
	return false;
}

void ShootingEnemy::process(float delta)
{
	auto nextPosition = this->getPosition() + m_description.addPosition;
	this->setPosition( nextPosition );
}

const float ShootingEnemyManager::INTERVAL = 0.08f;
ShootingEnemyManager::ShootingEnemyManager() :
m_interval( INTERVAL )
{
}

ShootingEnemyManager::~ShootingEnemyManager()
{
}

void ShootingEnemyManager::initialize()
{
}

void ShootingEnemyManager::finalize()
{
}

void ShootingEnemyManager::enter()
{
}

void ShootingEnemyManager::leave()
{
}

bool ShootingEnemyManager::input()
{
	return false;
}

void ShootingEnemyManager::process(float delta)
{
	// エネミーを作成
	m_interval -= delta;
	if( m_interval <= 0 )
	{
		ShootingEnemy::Description description;
		description.addPosition = Vec2( rand()%(4*2)-4, -4 );

		auto *pEnemy = ShootingEnemy::create( description );
		pEnemy->setPosition( Vec2(rand()%RESOLUTION_WIDTH, RESOLUTION_HEIGHT) );
		this->addChild( pEnemy );

		m_interval = INTERVAL;
	}
}

void ShootingEnemyManager::lateProcess(float delta)
{
	// 画面外のエネミーを削除する
	auto &children = this->getChildren();
	for( int i = 0; i < children.size(); i++ )
	{
		auto *pNode = children.at(i);
		auto position = GameUtility::localToWorldPosition( pNode );
		if( !GameUtility::isHit( position.x, position.y, 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT ) )
		{
			this->removeChild( pNode );
			i--;
		}
	}
}

void ShootingEnemyManager::addChild( ShootingEnemy *pEnemy )
{
	super::addChild( pEnemy );
}
