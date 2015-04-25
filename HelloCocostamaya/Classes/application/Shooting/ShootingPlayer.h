#pragma once
#include "common.h"
#include "ShootingCollider.h"

class ShootingBulletManager;
class ShootingPlayer : public ShootingCollider {

	typedef GameLayer super;

public:

	// 生成関数
	CREATE_FUNC(ShootingPlayer);

public:

	ShootingPlayer();
	~ShootingPlayer();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

};

class ShootingPlayerManager : public GameLayer {

	typedef GameLayer super;

public:

	// 生成関数
	CREATE_FUNC(ShootingPlayerManager);

public:

	ShootingPlayerManager();
	~ShootingPlayerManager();

	virtual void initialize() override;
	virtual void finalize() override;
	virtual void enter() override;
	virtual void leave() override;
	virtual bool input() override;
	virtual void process(float delta) override;

	ShootingPlayer *getPlayer() { return m_pPlayer;  }
	ShootingBulletManager *getBulletManager() { return m_pBulletManager; }

private:

	static const float BULLET_INTERVAL;
	static const float BULLET_SPEED;

	ShootingPlayer *m_pPlayer;
	ShootingBulletManager *m_pBulletManager;

	float m_bulletInterval;

};
