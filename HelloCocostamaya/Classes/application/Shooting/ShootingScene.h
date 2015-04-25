#pragma once
#include "common.h"

class ShootingScene : public GameScene {

	typedef GameScene super;

public:

	// 生成関数
	CREATE_FUNC(ShootingScene);

public:

	ShootingScene();
	~ShootingScene();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

};
