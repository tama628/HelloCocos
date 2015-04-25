#pragma once
#include "cocos2d.h"

class GameManager {

public:

	static GameManager *getInstance();

private:

	GameManager();
	~GameManager();

public:

	void initialize();
	void finalize();
	void process(float delta);

	cocos2d::Scene *getCurrentScene() const;
	cocos2d::Scene *getPreviousScene() const;

	void replaceScene(cocos2d::Scene *scene);
	void pushScene(cocos2d::Scene *scene);
	void popScene();
	void popScene(cocos2d::Scene *scene);
	void popToRootScene();

	CC_SYNTHESIZE_READONLY(float, m_delta, Delta);

};
