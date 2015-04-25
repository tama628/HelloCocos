#pragma once
#include "common.h"

class RootScene : public GameScene {

	typedef GameScene super;

public:

	// 生成関数
	CREATE_FUNC(RootScene);

	virtual void initialize() override;
	virtual void finalize() override;

};
