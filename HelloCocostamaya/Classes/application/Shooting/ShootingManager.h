#pragma once
#include "common.h"

class ShootingPlayerManager;
class ShootingEnemyManager;
class ShootingScore;
class ShootingManager : public GameLayer {

	typedef GameLayer super;

public:

	// 生成関数
	CREATE_FUNC(ShootingManager);

public:

	ShootingManager();
	~ShootingManager();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;
	virtual void lateProcess(float delta) override;

	void addScore();
	void updateScore();

private:

	ShootingPlayerManager *m_pPlayerManager;
	ShootingEnemyManager *m_pEnemyManager;
	
	// スコア
	int m_score;
	cocos2d::Label *m_pScoreLabel;

};
