#include "ShootingManager.h"

// Layer
#include "ShootingPlayer.h"
#include "ShootingEnemy.h"
#include "ShootingBullet.h"

USING_NS_CC;

ShootingManager::ShootingManager() :
m_pPlayerManager( nullptr ),
m_pEnemyManager( nullptr ),
m_score(0),
m_pScoreLabel(nullptr)
{
}

ShootingManager::~ShootingManager()
{
}

void ShootingManager::initialize()
{
	
	{
		const char *FONT_NAME = "fonts/arial.ttf";
		const int FONT_SIZE = 24;
		Label *pLabel = nullptr;

		// タイトル
		pLabel = Label::create("Shooting", FONT_NAME, FONT_SIZE);
		pLabel->setPosition(24, RESOLUTION_HEIGHT - 24);
		pLabel->setAnchorPoint(Vec2(0, 1.0f));
		pLabel->setColor(Color3B(255, 255, 255));
		pLabel->setZOrder(1.0f);
		this->addChild(pLabel);

		// ラベル
		pLabel = Label::create("", FONT_NAME, FONT_SIZE);
		pLabel->setPosition(RESOLUTION_WIDTH - 24, RESOLUTION_HEIGHT - 24);
		pLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
		pLabel->setAlignment( TextHAlignment::RIGHT );
		pLabel->setColor(Color3B(255, 255, 255));
		pLabel->setZOrder(1.0f);
		pLabel->setWidth(400);
		this->addChild(pLabel);

		m_pScoreLabel = pLabel;
	}

	// プレイヤー
	auto *pPlayerManager = ShootingPlayerManager::create();
	this->addChild(pPlayerManager);
	m_pPlayerManager = pPlayerManager;

	// エネミー
	auto *pEnemyManager = ShootingEnemyManager::create();
	this->addChild(pEnemyManager);
	m_pEnemyManager = pEnemyManager;
}

void ShootingManager::finalize()
{
}

void ShootingManager::enter()
{
}

void ShootingManager::leave()
{
}

bool ShootingManager::input()
{
	return false;
}

void ShootingManager::process(float delta)
{
}

void ShootingManager::lateProcess(float delta)
{
	// プレイヤーの弾とエネミーの当たり判定
	{
		auto *pBulletManager = m_pPlayerManager->getBulletManager();
		auto &bulletList = pBulletManager->getChildren();
		for( int i = 0; i < bulletList.size(); i++ )
		{
			auto *pBullet = static_cast<ShootingBullet*>(bulletList.at(i));
			
			auto &enemyList = m_pEnemyManager->getChildren();
			for( auto *pNode : enemyList )
			{
				auto *pEnemy = static_cast<ShootingEnemy*>(pNode);
				if( pBullet->isHit( pEnemy ) )
				{
					// スコア加算
					this->addScore();
					// エネミーを消す
					m_pEnemyManager->removeChild(pEnemy);
					// 弾を消す
					pBulletManager->removeChild( pBullet );
					// 弾のインデックスを戻す
					i--;
					// 次の弾へ
					break;
				}
			}
		}
	}

	// スコア更新
	this->updateScore();

	// プレイヤーとエネミーの当たり判定
	{
		auto *pPlayer = m_pPlayerManager->getPlayer();
		auto &enemyList = m_pEnemyManager->getChildren();
		for( auto *pNode : enemyList )
		{
			auto *pEnemy = static_cast<ShootingEnemy*>(pNode);
			if( pPlayer->isHit(pEnemy) )
			{
#ifndef NDEBUG
				// GameOver
				GameManager::getInstance()->popScene();
#endif
				break;
			}
		}
	}
}

void ShootingManager::addScore()
{
	m_score += 100;
}

void ShootingManager::updateScore()
{
	const int BUFFER_SIZE = 64;
	char buffer[BUFFER_SIZE];
	snprintf(buffer, BUFFER_SIZE, "score:%d", m_score);

	m_pScoreLabel->setString(buffer);
}
