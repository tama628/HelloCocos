#pragma once
#include "SpriteCommon.h"
#include "GameNode.h"

class GamePolygon;
class GameRectangle : public GameNode {

	typedef GameNode super;

public:

	static GameRectangle *create();
	GameRectangle();

protected:

	virtual bool init() override;
	
public:

	CC_SYNTHESIZE_PASS_BY_REF( cocos2d::Color4F, m_fillColor, FillColor );
	CC_SYNTHESIZE_PASS_BY_REF( cocos2d::Color4F, m_borderColor, BorderColor );
	CC_SYNTHESIZE ( float, m_borderSize, BorderSize );

	void update();

private:

	GamePolygon *m_pSprite;

};
