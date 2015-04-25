#include "GameManager.h"

// Scene
#if 0
#include "scene/root/RootScene.h"
#include "scene/title/TitleScene.h"
#include "scene/dungeon/DungeonScene.h"
#include "scene/battle/BattleScene.h"

#include "scene/debug/DebugScene.h"
#endif

USING_NS_CC;

static GameManager *g_pInstance;

GameManager *GameManager::getInstance()
{
	if( !g_pInstance )
	{
		g_pInstance = new GameManager();
	}
	return g_pInstance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::initialize()
{
}

void GameManager::finalize()
{
	// インスタンスの削除
	CC_SAFE_DELETE( g_pInstance );
}

void GameManager::process(float delta)
{
	m_delta = delta;
}

Scene *GameManager::getCurrentScene() const
{
	return Director::getInstance()->getRunningScene();
}

Scene *GameManager::getPreviousScene() const
{
	auto sceneStack = Director::getInstance()->getSceneStack();
	auto size = sceneStack.size();
	if( 1 < size )
	{
		return sceneStack.at( size - 2 );
	}
	return nullptr;
}

void GameManager::replaceScene(cocos2d::Scene *scene)
{
	Director::getInstance()->replaceScene( scene );
}

void GameManager::pushScene(cocos2d::Scene *scene)
{
	Director::getInstance()->pushScene( scene );
}

void GameManager::popScene()
{
	Director::getInstance()->popScene();
}

void GameManager::popScene(cocos2d::Scene *scene)
{
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene( scene, false );
}

void GameManager::popToRootScene()
{
	Director::getInstance()->popToRootScene();
}
