#include "RootScene.h"

#ifdef NDEBUG
#define BEGIN_SCENE SceneID::HELLO_WORLD
#else
#define BEGIN_SCENE SceneID::DEBUG
#endif

USING_NS_CC;

void RootScene::initialize()
{
	// initialize
	GameManager::getInstance()->initialize();
	InputManager::getInstance()->initialize();

	// change scene
	auto scene = CreateScene( BEGIN_SCENE );
	GameManager::getInstance()->pushScene( scene );
}

void RootScene::finalize()
{
	// finalize
	InputManager::getInstance()->finalize();
	GameManager::getInstance()->finalize();
}
