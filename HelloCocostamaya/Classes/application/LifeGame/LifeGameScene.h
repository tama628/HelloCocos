#pragma once
#include "common.h"

class LifeGameScene : public GameScene {

	typedef GameScene super;

public:

	// 生成関数
	CREATE_FUNC(LifeGameScene);

public:

	// セルの状態
	enum STATUS
	{
		STATUS_DEAD,
		STATUS_ALIVE,
		STATUS_MAX
	};

	// セル情報
	struct Sell
	{
		STATUS current;
		STATUS next;
		cocos2d::Sprite *pSprite;
	};

	// 定数
	static const int SELL_X = 0;
	static const int SELL_Y = 0;
	static const int SELL_WIDTH = 10;
	static const int SELL_HEIGHT = 10;
	static const int SELL_COLUMN = RESOLUTION_WIDTH / SELL_WIDTH;
	static const int SELL_ROW = RESOLUTION_HEIGHT / SELL_HEIGHT;
	static const cocos2d::Color3B SELL_COLOR[ STATUS_MAX ];

	// セルの更新時間
	static const float SELL_UPDATE_TIME;
	
public:

	LifeGameScene();
	~LifeGameScene();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

private:

	// セルの更新処理
	void updateSell();
	// (x, y)に隣接する生存しているセル数を返す
	int calculateAliveCount(int x, int y);
	// 配列内か返す
	bool isSellContain(int x, int y);

private:

	// セルの更新時間
	int m_sellUpdateTime;
	// セル
	Sell m_sell[SELL_ROW][SELL_COLUMN];

};
