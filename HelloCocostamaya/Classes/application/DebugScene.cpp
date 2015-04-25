#ifndef NDEBUG

#include "DebugScene.h"

#include <functional>

USING_NS_CC;

// 定数
static const int POSITION_X = 32;
static const int POSITION_Y = RESOLUTION_HEIGHT - 32;
static const int POSITION_CURSOR_X = POSITION_X-16;
static const int POSITION_CURSOR_Y = POSITION_Y;
static const int FONT_SIZE = 24;
static const int OFFSET_Y = -FONT_SIZE;
static const Color3B FONT_COLOR(255, 255, 255);

// メニュー項目
enum MENU {
	MENU_DEBUG_STATUS,
	MENU_HELLO_WORLD,
	MENU_LIFE_GAME,
	MENU_SHOOTING,

	MENU_MAX
};

// メニュー名
static const char *const MENU_NAME[ MENU_MAX ] = {
	"DebugStatus",
	"HelloWorld",
	"LifeGame",
	"Shooting"
};

// メニュー処理
std::function<void(void)> MENU_FUNC[ MENU_MAX ] = {
	[]{ Director::getInstance()->setDisplayStats( !Director::getInstance()->isDisplayStats() ); },
	[]{ GameManager::getInstance()->pushScene( CreateScene( SceneID::HELLO_WORLD ) ); },
	[]{ GameManager::getInstance()->pushScene( CreateScene( SceneID::LIFE_GAME ) ); },
	[]{ GameManager::getInstance()->pushScene( CreateScene( SceneID::SHOOTING ) ); }
};

DebugScene::DebugScene() :
m_pLayer(nullptr),
m_cursor(0),
m_pCursorLabel(nullptr)
{
}

DebugScene::~DebugScene()
{
}

void DebugScene::initialize()
{
	// レイヤーの作成
	auto *pLayer = GameLayer::create();
	this->addChild( pLayer );
	m_pLayer = pLayer;

	// メニューの作成
	{
		const char *FONT_DEFAULT = "fonts/arial.ttf";

		// カーソル
		{
			m_pCursorLabel = Label::create(">", FONT_DEFAULT, FONT_SIZE);
			m_pCursorLabel->setAnchorPoint( Vec2(0, 1) );
			m_pCursorLabel->setColor( FONT_COLOR );
			pLayer->addChild( m_pCursorLabel, 0 );
			this->updateCursor();
		}

		// 項目
		for( int i = 0; i < MENU_MAX; i++ )
		{
			auto *pText = Label::create(MENU_NAME[i], FONT_DEFAULT, FONT_SIZE);
			pText->setPosition( Vec2(POSITION_X, POSITION_Y+OFFSET_Y*i) );
			pText->setAnchorPoint( Vec2(0, 1) );
			pText->setColor( FONT_COLOR );
			pText->setTag(i);
			pLayer->addChild( pText );
		}
	}
}

void DebugScene::finalize()
{
}

void DebugScene::enter()
{
}

void DebugScene::leave()
{
}

bool DebugScene::input()
{
	// キー判定
	const auto &key = GetKeyManager();
	if( key.isPush( KeyCode::KEY_KP_ENTER ) )
	{
		( MENU_FUNC[ m_cursor ] )();
		return true;
	}
	else if( key.isPressRepeatFast( KeyCode::KEY_UP_ARROW ) )
	{
		m_cursor = (m_cursor+MENU_MAX-1) % MENU_MAX;
		this->updateCursor();
		return true;
	}
	else if( key.isPressRepeatFast( KeyCode::KEY_DOWN_ARROW ) )
	{
		m_cursor = (m_cursor+1) % MENU_MAX;
		this->updateCursor();
		return true;
	}

	// タッチ判定
	const auto &touch = GetTouchManager();
	if( touch.isGesture( TouchCode::TOUCH_TAP ) )
	{
		auto info = touch.getTouchInfo();
		auto position = info->getPosition();
		CCLOG( "touch=( %f, %f )", position.x, position.y );

		for( int i = 0; i < MENU_MAX; i++ )
		{
			Node *pNode = m_pLayer->getChildByTag(i);
			if( pNode )
			{
				if( GameUtility::isHit(position, pNode) )
				{
					( MENU_FUNC[i] )();
					return true;
				}
			}
		}
	}

	return false;
}

void DebugScene::process(float delta)
{
}

void DebugScene::updateCursor()
{
	m_pCursorLabel->setPosition( Point(POSITION_CURSOR_X, POSITION_CURSOR_Y+OFFSET_Y*m_cursor) );
}

#endif // #ifndef NDEBUG
