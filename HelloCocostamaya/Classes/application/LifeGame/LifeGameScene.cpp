#include "LifeGameScene.h"

USING_NS_CC;

const Color3B LifeGameScene::SELL_COLOR[ STATUS_MAX ] = {
	{ 0, 0, 0 },
	{ 0, 255, 0}
};

const float LifeGameScene::SELL_UPDATE_TIME = 0.08f;

LifeGameScene::LifeGameScene() :
m_sellUpdateTime(SELL_UPDATE_TIME)
{
}

LifeGameScene::~LifeGameScene()
{
}

void LifeGameScene::initialize()
{
	auto *pDirector = Director::getInstance();

	// レイヤーの作成
	auto *pLayer = GameLayer::create();
	this->addChild( pLayer );

	// タイトル
	auto *pLabel = Label::create("LifeGame", "fonts/arial.ttf", 24);
	pLabel->setPosition(24, RESOLUTION_HEIGHT - 24);
	pLabel->setAnchorPoint(Vec2(0, 1.0f));
	pLabel->setColor(Color3B(255, 255, 255));
	pLabel->setZOrder(1.0f);
	pLayer->addChild(pLabel);

	// セル
	for( int y = 0; y < SELL_ROW; y++ )
	{
		for( int x = 0; x < SELL_COLUMN; x++ )
		{
			auto *pSprite = Sprite::create( "LifeGame/common_base.png" );
			auto position = pDirector->convertToGL( Vec2(SELL_X + SELL_WIDTH*x, SELL_Y + SELL_HEIGHT*y) );
			pSprite->setPosition( position );
			pSprite->setAnchorPoint( Vec2(0, 1) );
			pSprite->setScale( SELL_WIDTH, SELL_HEIGHT );
			pLayer->addChild( pSprite );

			Sell &sell = m_sell[y][x];
			sell.current = static_cast<STATUS>( rand()%STATUS_MAX );
			sell.next = STATUS_DEAD;
			sell.pSprite = pSprite;
			sell.pSprite->setColor( SELL_COLOR[sell.current] );
		}
	}
}

void LifeGameScene::finalize()
{
}

void LifeGameScene::enter()
{
}

void LifeGameScene::leave()
{
}

bool LifeGameScene::input()
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

	if( touch.isGesture( TouchCode::TOUCH_TAP ) )
	{
		for( int y = 0; y < SELL_ROW; y++ )
		{
			for( int x = 0; x < SELL_COLUMN; x++ )
			{
				Sell &sell = m_sell[y][x];
				sell.current = static_cast<STATUS>( rand()%STATUS_MAX );
			}
		}
		return true;
	}

	return false;
}

void LifeGameScene::process(float delta)
{
	// 更新時間の計算
	m_sellUpdateTime -= delta;

	// 更新時間に達しているか
	if( 0 < m_sellUpdateTime ) return;

	// 更新
	this->updateSell();

	// 更新時間をセット
	m_sellUpdateTime = SELL_UPDATE_TIME;
}

void LifeGameScene::updateSell()
{
	// 計算
	for( int y = 0; y < SELL_ROW; y++ )
	{
		for( int x = 0; x < SELL_COLUMN; x++ )
		{
			Sell &sell = m_sell[y][x];
			int aliveCount = this->calculateAliveCount(x, y);

			switch( sell.current )
			{
				case STATUS_DEAD:
				{
					// 誕生
					if( aliveCount == 3 )
					{
						sell.next = STATUS_ALIVE;
					}
					break;
				}
				case STATUS_ALIVE:
				{
					// 過疎 || 過密
					if( aliveCount <= 1 || 4 <= aliveCount )
					{
						sell.next = STATUS_DEAD;
					}
					break;
				}
			}
		}
	}

	// 更新
	for( int y = 0; y < SELL_ROW; y++ )
	{
		for( int x = 0; x < SELL_COLUMN; x++ )
		{
			Sell &sell = m_sell[y][x];
			sell.current = sell.next;
			sell.pSprite->setColor(SELL_COLOR[sell.current]);
		}
	}
}

int LifeGameScene::calculateAliveCount(int x, int y)
{
	Sell &sell = m_sell[y][x];
	int alive = 0;

	for( int addY = -1; addY <= 1; addY++ )
	{
		for( int addX = -1; addX <= 1; addX++ )
		{
			int xx = x + addX;
			int yy = y + addY;

			if( xx == x && yy == y )
				continue;

			if( !this->isSellContain(xx, yy) )
				continue;

			if( m_sell[yy][xx].current == STATUS_ALIVE )
				alive++;
		}
	}

	return alive;
}

bool LifeGameScene::isSellContain(int x, int y)
{
	return 0 <= x && x < SELL_COLUMN && 0 <= y && y < SELL_ROW;
}
