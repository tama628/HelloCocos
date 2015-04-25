#pragma once
#include "cocos2d.h"

class GameScene : public cocos2d::Scene {

	typedef cocos2d::Scene super;

public:

    // 生成関数
    CREATE_FUNC(GameScene);

public:

	GameScene();
	virtual ~GameScene();

protected:

	// cocos2d-x methods.
	virtual bool init() override final;
	virtual void cleanup() override final;
	virtual void onEnter() override final;
	virtual void onExit() override final;
	virtual void onEnterTransitionDidFinish() override final;
	virtual void onExitTransitionDidStart() override final;
	virtual void update(float delta) override final;

	// method for this game.
	virtual bool prepare();
	virtual void initialize();
	virtual void finalize();
	virtual void enter();
	virtual void leave();
	virtual void attach();
	virtual void detach();
	virtual bool input();
	virtual void process(float delta);
	virtual void lateProcess(float delta);

public:

	// 外部から初期化破棄したいとき
	virtual void _initialize();
	virtual void _finalize();

private:

	bool m_initializeFlag;

};
