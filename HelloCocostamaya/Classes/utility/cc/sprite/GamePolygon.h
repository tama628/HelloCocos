#pragma once
#include "SpriteCommon.h"

class GamePolygon : public cocos2d::DrawNode {

	typedef cocos2d::DrawNode super;

public:

	virtual void defaultSetting();

	static GamePolygon *create();

	GAME_SPRITE_POSITION_ACCESSOR();
	GAME_SPRITE_ANCHOR_ACCESSOR();

};
