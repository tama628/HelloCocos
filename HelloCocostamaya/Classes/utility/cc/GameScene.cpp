#include "GameScene.h"

// Common
#include "GameManager.h"
#include "input/InputManager.h"

GameScene::GameScene() :
m_initializeFlag(false)
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
    if( !super::init() )
    {
        return false;
    }
	this->scheduleUpdate();
	return this->prepare();
}

void GameScene::cleanup()
{
	this->_finalize();
	super::cleanup();
}

void GameScene::onEnter()
{
	this->_initialize();
	this->enter();
	super::onEnter();

	// clear
	InputManager *pInputManager = InputManager::getInstance();
	pInputManager->clear();
}

void GameScene::onExit()
{
	this->leave();
	super::onExit();
}

void GameScene::onEnterTransitionDidFinish()
{
	this->attach();
	super::onEnterTransitionDidFinish();
}

void GameScene::onExitTransitionDidStart()
{
	this->detach();
	super::onExitTransitionDidStart();
}

void GameScene::update(float delta)
{
	GameManager *pGameManager = GameManager::getInstance();
	InputManager *pInputManager = InputManager::getInstance();

	// manager
	pGameManager->process(delta);
	pInputManager->process(delta);

	// input()
	bool ret = this->input();
	pInputManager->setTemporaryInputFlag( !ret );

	// process()
	this->process(delta);

	// to base class
	super::update(delta);

	// to children
	for( Node *pNode : this->getChildren() )
	{
		pNode->update( delta );
	}

	// lateProcess()
	this->lateProcess(delta);

	// manager
	pInputManager->lateProcess(delta);
}

bool GameScene::prepare()
{
	return true;
}

void GameScene::initialize()
{
}

void GameScene::finalize()
{
}

void GameScene::enter()
{
}

void GameScene::leave()
{
}

void GameScene::attach()
{
}

void GameScene::detach()
{
}

bool GameScene::input()
{
	return false;
}

void GameScene::process(float delta)
{
}

void GameScene::lateProcess(float delta)
{
}

void GameScene::_initialize()
{
	if( !m_initializeFlag )
	{
		this->initialize();
		m_initializeFlag = true;
	}
}

void GameScene::_finalize()
{
	if( m_initializeFlag )
	{
		this->finalize();
		m_initializeFlag = false;
	}
}
