#include "GameRectangle.h"
#include "GamePolygon.h"

USING_NS_CC;

GameRectangle* GameRectangle::create()
{
    auto *pSprite = new(std::nothrow) GameRectangle();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

GameRectangle::GameRectangle() :
m_fillColor( 0, 0, 0, 0 ),
m_borderColor( 0, 0, 0, 0 ),
m_borderSize( 0 ),
m_pSprite( nullptr )
{}

bool GameRectangle::init()
{
	bool result = super::init();
	if( !result ) return false;

	auto *pSprite = GamePolygon::create();
	if( !pSprite ) return false;

	this->addChild( pSprite );
	m_pSprite = pSprite;
	return true;
}

void GameRectangle::update()
{
	const Size &size = this->getContentSize();

	const int VERTEX_MAX = 4;
	const Vec2 VERTEX_ARRAY[ VERTEX_MAX ] = {
		{ 0, 0 },
		{ 0, -size.height },
		{ size.width, -size.height },
		{ size.width, 0 }
	};

	m_pSprite->drawPolygon( VERTEX_ARRAY, VERTEX_MAX, m_fillColor, m_borderSize, m_borderColor );
}
