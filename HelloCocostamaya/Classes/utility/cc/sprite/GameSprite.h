#pragma once
#include "SpriteCommon.h"

class GameSprite : public cocos2d::Sprite {

	typedef cocos2d::Sprite super;

public:

	virtual void defaultSetting();

	static GameSprite *create();
    static GameSprite *create(const char *filename);

	GAME_SPRITE_POSITION_ACCESSOR();
	GAME_SPRITE_ANCHOR_ACCESSOR();

	void setScaleBySize(const cocos2d::Size& size);

};
