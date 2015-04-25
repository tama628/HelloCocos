#include "GamePolygon.h"

USING_NS_CC;

void GamePolygon::defaultSetting()
{
	this->setPosition( Vec2(0,0) );
	this->setAnchorPoint( Vec2(0,0) );
}

GamePolygon* GamePolygon::create()
{
    auto *pSprite = new(std::nothrow) GamePolygon();
    if (pSprite && pSprite->init())
    {
		pSprite->defaultSetting();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return nullptr;
}
