#pragma once
#include "SpriteCommon.h"

class GameNode : public cocos2d::Node {

	typedef cocos2d::Node super;

public:

	virtual void defaultSetting();

	static GameNode *create();

	// GL to UI.
	virtual const cocos2d::Vec2 &getPosition() const override;
	virtual void setPosition(const cocos2d::Vec2& pos) override;
	virtual const cocos2d::Vec2 &getAnchorPoint() const override;
	virtual void setAnchorPoint(const cocos2d::Vec2& anchor) override;

private:

	mutable cocos2d::Vec2 m_temporaryPosition;
	mutable cocos2d::Vec2 m_temporaryAnchor;

};
