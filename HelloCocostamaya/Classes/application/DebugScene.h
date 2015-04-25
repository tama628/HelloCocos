#ifndef NDEBUG

#pragma once
#include "common.h"

class DebugScene : public GameScene {

	typedef GameScene super;

public:

	// 生成関数
	CREATE_FUNC(DebugScene);

public:

	// コンストラクタ
	DebugScene();
	// デストラクタ
	~DebugScene();

	// 初期化
	virtual void initialize() override;
	// 破棄
	virtual void finalize() override;
	// アクティブになるときの処理
	virtual void enter() override;
	// 非アクティブになるときの処理
	virtual void leave() override;
	// 入力処理
	virtual bool input() override;
	// 更新処理
	virtual void process(float delta) override;

private:

	// カーソルの更新
	void updateCursor();

private:

	// レイヤー
	GameLayer *m_pLayer;

	// カーソル
	int m_cursor;
	cocos2d::Label *m_pCursorLabel;

};

#endif // #ifndef NDEBUG
