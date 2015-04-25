#pragma once
#include "cocos2d.h"

class GameLayer : public cocos2d::Layer {

	typedef cocos2d::Layer super;

public:

    // 生成関数
    CREATE_FUNC(GameLayer);

public:

	GameLayer();
	virtual ~GameLayer();

	virtual void defaultSetting();

protected:

	// cocos2d-x methods.
	virtual bool init() override final;
	virtual void cleanup() override final;
	virtual void onEnter() override final;
	virtual void onExit() override final;
	virtual void onEnterTransitionDidFinish() override final;
	virtual void onExitTransitionDidStart() override final;
	virtual void update(float delta) override final;

protected:

	void onBeforeVisitScissor();
	void onAfterVisitScissor();

	// cocos2d-x method.
	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

protected:

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

	// for clipping.
	bool getClipFlag() const;
	void setClipFlag(bool flag);
	const cocos2d::Rect &getClipArea() const;
	void setClipArea(const cocos2d::Rect &rect);

private:

	bool m_initializeFlag;

	// for clipping.
	cocos2d::CustomCommand _beforeVisitCmdScissor;
	cocos2d::CustomCommand _afterVisitCmdScissor;
	bool m_clipFlag;
	cocos2d::Rect m_clipArea;

};

inline bool GameLayer::getClipFlag() const
{
	return m_clipFlag;
}

inline void GameLayer::setClipFlag(bool flag)
{
	m_clipFlag = flag;
}

inline const cocos2d::Rect &GameLayer::getClipArea() const
{
	return m_clipArea;
}

inline void GameLayer::setClipArea(const cocos2d::Rect &rect)
{
	m_clipArea = rect;
}
