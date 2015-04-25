#include "GameLayer.h"

// Common
#include "GameManager.h"
#include "input/InputManager.h"

// Utility
#include "GameUtility.h"

USING_NS_CC;

GameLayer::GameLayer() :
m_initializeFlag(false),
m_clipFlag(false),
m_clipArea(0, 0, 0, 0)
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::defaultSetting()
{
	this->setPosition( Vec2(0,0) );
	this->setAnchorPoint( Vec2(0,0) );
}

bool GameLayer::init()
{
    if( !super::init() )
    {
        return false;
    }
	// this->scheduleUpdate();
	this->defaultSetting();
	return this->prepare();
}

void GameLayer::cleanup()
{
	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->cleanup();
		}
	}

	this->_finalize();
	super::cleanup();
}

void GameLayer::onEnter()
{
	this->_initialize();
	this->enter();
	super::onEnter();

	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->onEnter();
		}
	}
}

void GameLayer::onExit()
{
	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->onExit();
		}
	}

	this->leave();
	super::onExit();
}

void GameLayer::onEnterTransitionDidFinish()
{
	this->attach();
	super::onEnterTransitionDidFinish();

	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->onEnterTransitionDidFinish();
		}
	}
}

void GameLayer::onExitTransitionDidStart()
{
	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->onExitTransitionDidStart();
		}
	}

	this->detach();
	super::onExitTransitionDidStart();
}


void GameLayer::update(float delta)
{
	GameManager *pGameManager = GameManager::getInstance();
	InputManager *pInputManager = InputManager::getInstance();

	// input()
	if( pInputManager->isValid() )
	{
		bool ret = this->input();
		pInputManager->setTemporaryInputFlag( !ret );
	}

	// process()
	this->process(delta);

	// to subClass
	super::update(delta);
    {
		for( Node *pNode : this->getChildren() )
		{
			GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
			if( pGameLayer )
			{
				pGameLayer->update( delta );
			}
		}
    }

	// lateProcess()
	this->lateProcess(delta);
}

void GameLayer::onBeforeVisitScissor()
{
	glEnable( GL_SCISSOR_TEST );

	// add parent position
	Vec2 position(0,0);
	Node *pParent = this->getParent();
	if( pParent )
	{
		GameUtility::localToWorldPosition( pParent );
	}

	// UI to GL View
	Vec2 uiPosition = position + m_clipArea.origin;
	Vec2 glPosition = Director::getInstance()->convertToGL( uiPosition );
	float x = glPosition.x;
	float y = glPosition.y - m_clipArea.size.height;
	float w = m_clipArea.size.width;
	float h = m_clipArea.size.height;

	// glScissor()
	GLView *pGLView = Director::getInstance()->getOpenGLView();
	pGLView->setScissorInPoints( x, y, w, h );
}

void GameLayer::onAfterVisitScissor()
{
	glDisable( GL_SCISSOR_TEST );
}

void GameLayer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	// Cut the view
	if( this->isVisible() )
	{
		if( !m_clipFlag )
		{
			// default process.
			super::visit(renderer, parentTransform, parentFlags);
		}
		else
		{
			// setup scissor test.
			_beforeVisitCmdScissor.init(_globalZOrder);
			_beforeVisitCmdScissor.func = CC_CALLBACK_0(GameLayer::onBeforeVisitScissor, this);
			renderer->addCommand(&_beforeVisitCmdScissor);

			// default process.
			super::visit(renderer, parentTransform, parentFlags);

			_afterVisitCmdScissor.init(_globalZOrder);
			_afterVisitCmdScissor.func = CC_CALLBACK_0(GameLayer::onAfterVisitScissor, this);
			renderer->addCommand(&_afterVisitCmdScissor);
		}
	}
}

bool GameLayer::prepare()
{
	return true;
}

void GameLayer::initialize()
{
}

void GameLayer::finalize()
{
}

void GameLayer::enter()
{
}

void GameLayer::leave()
{
}

void GameLayer::attach()
{
}

void GameLayer::detach()
{
}

bool GameLayer::input()
{
	return false;
}

void GameLayer::process(float delta)
{
}

void GameLayer::lateProcess(float delta)
{
}

void GameLayer::_initialize()
{
	if( !m_initializeFlag )
	{
		this->initialize();
		m_initializeFlag = true;
	}

	// children
	for( Node *pNode : this->getChildren() )
	{
		GameLayer *pGameLayer = dynamic_cast<GameLayer*>( pNode );
		if( pGameLayer )
		{
			pGameLayer->_initialize();
		}
	}
}

void GameLayer::_finalize()
{
	if( m_initializeFlag )
	{
		this->finalize();
		m_initializeFlag = false;
	}
}
