#pragma once
#include "cocos2d.h"

// 左上基点に変換
#define GAME_SPRITE_POSITION_ACCESSOR() \
private: \
mutable cocos2d::Vec2 m_temporaryPosition; \
public: \
virtual const cocos2d::Vec2 &getPosition() const override\
{ \
	using namespace cocos2d; \
	Director *pDirector = Director::getInstance(); \
    Size visibleSize = pDirector->getVisibleSize(); \
    Vec2 origin = pDirector->getVisibleOrigin(); \
	Vec2 ret = super::getPosition(); \
	ret.x = ret.x - origin.x; \
	ret.y = -(ret.y - visibleSize.height) - origin.y; \
	return m_temporaryPosition = ret; \
} \
virtual float getPositionX() const override \
{ \
	return getPosition().x; \
} \
virtual float getPositionY() const override \
{ \
	return getPosition().y; \
} \
virtual void setPosition(const cocos2d::Vec2& position) override \
{ \
	using namespace cocos2d; \
	Director *pDirector = Director::getInstance(); \
    Size visibleSize = pDirector->getVisibleSize(); \
    Vec2 origin = pDirector->getVisibleOrigin(); \
	super::setPosition( Vec2(position.x + origin.x, -(position.y + origin.y) + visibleSize.height ) ); \
} \
virtual void setPositionX(float x) override \
{ \
	using namespace cocos2d; \
	Vec2 position = getPosition(); \
	setPosition( Vec2(x, position.y) ); \
} \
virtual void setPositionY(float y) override \
{ \
	using namespace cocos2d; \
	Vec2 position = getPosition(); \
	setPosition( Vec2(position.x, y) ); \
}

// 左上基点に変換
#define GAME_SPRITE_ANCHOR_ACCESSOR() \
private: \
mutable cocos2d::Vec2 m_temporaryAnchor; \
public: \
virtual const cocos2d::Vec2 &getAnchorPoint() const override\
{ \
	using namespace cocos2d; \
	Vec2 ret = super::getAnchorPoint(); \
	ret.y = 1.0f - ret.y; \
	return m_temporaryAnchor = ret; \
} \
virtual void setAnchorPoint(const cocos2d::Vec2& anchor) override\
{ \
	using namespace cocos2d; \
	super::setAnchorPoint( Vec2(anchor.x, 1.0f - anchor.y) ); \
}
