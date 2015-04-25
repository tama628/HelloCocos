#pragma once
#include "common.h"
#include "ShootingCollider.h"

class ShootingEnemy : public ShootingCollider {

	typedef GameLayer super;

private:

	// 生成関数
	CREATE_FUNC(ShootingEnemy);

public:

	struct Description {
		cocos2d::Vec2 addPosition;
		Description() :
		addPosition( cocos2d::Vec2::ZERO )
		{}
	};

	static ShootingEnemy *create( const Description &description );

public:

	ShootingEnemy();
	~ShootingEnemy();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

private:

	Description m_description;

};

class ShootingEnemyManager : public GameLayer {

	typedef GameLayer super;

public:

	// 生成関数
	CREATE_FUNC(ShootingEnemyManager);

public:

	ShootingEnemyManager();
	~ShootingEnemyManager();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;
	virtual void lateProcess(float delta) override;

	// 弾の追加
	void addChild( ShootingEnemy *pEnemy );

private:

	static const float INTERVAL;
	float m_interval;

};
