#include "GameSprite.h"

USING_NS_CC;

void GameSprite::defaultSetting()
{
	this->setPosition( Vec2(0,0) );
	this->setAnchorPoint( Vec2(0,0) );
}

GameSprite* GameSprite::create()
{
    auto *pSprite = new(std::nothrow) GameSprite();
    if (pSprite && pSprite->init())
    {
		pSprite->defaultSetting();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

GameSprite* GameSprite::create(const char *filename)
{
    auto *pSprite = new(std::nothrow) GameSprite();
    if (pSprite && pSprite->initWithFile(filename))
    {
		pSprite->defaultSetting();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

void GameSprite::setScaleBySize(const cocos2d::Size &size)
{
	const cocos2d::Size &contentSize = this->getContentSize();
	float scaleX = size.width / contentSize.width;
	float scaleY = size.height / contentSize.height;
	this->setScale( scaleX, scaleY );
}
