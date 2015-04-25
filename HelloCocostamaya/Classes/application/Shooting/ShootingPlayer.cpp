#include "ShootingPlayer.h"

// Layer
#include "ShootingBullet.h"

USING_NS_CC;

const float ShootingPlayerManager::BULLET_INTERVAL = 0.04f;
const float ShootingPlayerManager::BULLET_SPEED = 6.0f;

ShootingPlayer::ShootingPlayer()
{
}

ShootingPlayer::~ShootingPlayer()
{
}

void ShootingPlayer::initialize()
{
	const int VERTEX_MAX = 4;
	const Size PLAYER_SIZE = { 16, 16 };
	const Size PLAYER_SIZE_HALF = PLAYER_SIZE / 2;
	const Vec2 VERTEX_ARRAY[VERTEX_MAX] = {
		{ -PLAYER_SIZE_HALF.width, -PLAYER_SIZE_HALF.height },
		{ -PLAYER_SIZE_HALF.width, PLAYER_SIZE_HALF.height },
		{ PLAYER_SIZE_HALF.width, PLAYER_SIZE_HALF.height },
		{ PLAYER_SIZE_HALF.width, -PLAYER_SIZE_HALF.height }
	};

	auto *pSprite = DrawNode::create();
	pSprite->drawPolygon(VERTEX_ARRAY, VERTEX_MAX, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 1));
	this->addChild(pSprite);
	
	this->setCollider(Rect(-PLAYER_SIZE_HALF.width, -PLAYER_SIZE_HALF.height, PLAYER_SIZE.width, PLAYER_SIZE.height));
}

void ShootingPlayer::finalize()
{
}

void ShootingPlayer::enter()
{
}

void ShootingPlayer::leave()
{
}

bool ShootingPlayer::input()
{
	return false;
}

void ShootingPlayer::process(float delta)
{
}

ShootingPlayerManager::ShootingPlayerManager() :
m_pPlayer(nullptr),
m_pBulletManager( nullptr ),
m_bulletInterval( 0 )
{
}

ShootingPlayerManager::~ShootingPlayerManager()
{
}

void ShootingPlayerManager::initialize()
{
	const int VERTEX_MAX = 4;
	const Size PLAYER_SIZE = { 16, 16 };
	const Size PLAYER_SIZE_HALF = PLAYER_SIZE/2;
	const Vec2 VERTEX_ARRAY[ VERTEX_MAX ] = {
		{ -PLAYER_SIZE_HALF.width, -PLAYER_SIZE_HALF.height },
		{ -PLAYER_SIZE_HALF.width, PLAYER_SIZE_HALF.height },
		{ PLAYER_SIZE_HALF.width, PLAYER_SIZE_HALF.height },
		{ PLAYER_SIZE_HALF.width, -PLAYER_SIZE_HALF.height }
	};

	auto *pPlayer = ShootingPlayer::create();
	this->addChild(pPlayer);
	m_pPlayer = pPlayer;

	auto *pBulletManager = ShootingBulletManager::create();
	this->addChild( pBulletManager );
	
	m_pBulletManager = pBulletManager;
}

void ShootingPlayerManager::finalize()
{
}

void ShootingPlayerManager::enter()
{
}

void ShootingPlayerManager::leave()
{
}

bool ShootingPlayerManager::input()
{
	float delta = GameManager::getInstance()->getDelta();
	const auto &touch = GetTouchManager();

	// 座標更新
	{
		auto position = touch.getMousePosition();
		m_pPlayer->setPosition(position);
	}

	if( touch.isGesture( TouchCode::TOUCH_DOWN ) ||
		( touch.isGesture( TouchCode::TOUCH_PRESS ) && (m_bulletInterval-=delta) <= 0 ) )
	{
		auto info = touch.getTouchInfo();
		auto position = info->getPosition();
		auto direction = -info->getPastTravel();

		if( 0 < direction.length() )
		{
			direction.normalize();

#if 1
			// ランダムで弾を散らす
			const int DEGREE_SCATTER = 30;
			float radian = atan2( direction.y, direction.x );
			float addDegree = rand() % (DEGREE_SCATTER*2) - DEGREE_SCATTER;
			radian += GameUtility::degreeToRadian(addDegree);
			direction.x = cos(radian);
			direction.y = sin(radian);
#endif

			direction *= BULLET_SPEED;

			ShootingBullet::Description description;
			description.addPosition = direction;
			description.size = 8;
			description.color = Color4F::BLUE;

			auto *pBullet = ShootingBullet::create( description );
			pBullet->setPosition(m_pPlayer->getPosition());
			m_pBulletManager->addChild( pBullet );
		}

		m_bulletInterval = BULLET_INTERVAL;
	}

	return false;
}

void ShootingPlayerManager::process(float delta)
{
}
