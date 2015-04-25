#include "GameNode.h"

USING_NS_CC;

void GameNode::defaultSetting()
{
	this->setPosition( Vec2(0,0) );
	this->setAnchorPoint( Vec2(0,0) );
}

GameNode* GameNode::create()
{
    auto *pSprite = new(std::nothrow) GameNode();
    if (pSprite && pSprite->init())
    {
		pSprite->defaultSetting();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

const Vec2 &GameNode::getPosition() const
{
	Vec2 ret = super::getPosition();
	ret.y = -ret.y;
	return m_temporaryPosition = ret;
}

void GameNode::setPosition(const Vec2& pos)
{
	super::setPosition( Vec2(pos.x, -pos.y) );
}

const Vec2 &GameNode::getAnchorPoint() const
{
	Vec2 ret = super::getAnchorPoint();
	ret.y = -ret.y;
	return m_temporaryAnchor = ret;
}

void GameNode::setAnchorPoint(const Vec2& anchor)
{
	super::setAnchorPoint( Vec2(anchor.x, -anchor.y) );
}
