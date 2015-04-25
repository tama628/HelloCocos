#include "ShootingScene.h"

// Layer
#include "ShootingManager.h"

USING_NS_CC;

ShootingScene::ShootingScene()
{
}

ShootingScene::~ShootingScene()
{
}

void ShootingScene::initialize()
{
	auto *pManager = ShootingManager::create();
	this->addChild( pManager );
}

void ShootingScene::finalize()
{
}

void ShootingScene::enter()
{
}

void ShootingScene::leave()
{
}

bool ShootingScene::input()
{
	// タッチ判定
	const auto &touch = GetTouchManager();

#ifndef NDEBUG
	if( touch.isGesture( TouchCode::TOUCH_DOUBLE_TAP ) )
	{
		GameManager::getInstance()->popScene();
		return true;
	}
#endif

	return false;
}

void ShootingScene::process(float delta)
{
}
