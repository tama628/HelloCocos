#pragma once
#include "common.h"
#include "ShootingCollider.h"

class ShootingBullet : public ShootingCollider {

	typedef GameLayer super;

private:

	// 生成関数
	CREATE_FUNC(ShootingBullet);

public:

	struct Description {
		cocos2d::Vec2 addPosition;
		float size;
		cocos2d::Color4F color;
		Description() :
		addPosition( cocos2d::Vec2::ZERO ),
		size(0),
		color( cocos2d::Color4F::BLACK )
		{}
	};

	static ShootingBullet *create( const Description &description );

public:

	ShootingBullet();
	~ShootingBullet();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

private:

	Description m_description;

};

class ShootingBulletManager : public GameLayer {

	typedef GameLayer super;

public:

	// 生成関数
	CREATE_FUNC(ShootingBulletManager);

public:

	ShootingBulletManager();
	~ShootingBulletManager();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;
	virtual void lateProcess(float delta) override;

	// 弾の追加
	void addChild( ShootingBullet *pBullet );

};
