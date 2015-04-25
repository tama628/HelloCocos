#pragma once
#include "SpriteCommon.h"

class GameLabel : public cocos2d::Label {

	typedef cocos2d::Label super;

protected:

    GameLabel(cocos2d::FontAtlas *atlas = nullptr, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT, 
        cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);

	virtual void defaultSetting();

public:

    static GameLabel * create(const char *fontName, float fontSize,
                             const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::CENTER,
                             cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
    static GameLabel * createWithSystemFont(const char *fontName, float fontSize,
                             const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::CENTER,
                             cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);
    static GameLabel * createWithTTF(const char *fontName, float fontSize,
                             const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::CENTER,
                             cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	GAME_SPRITE_POSITION_ACCESSOR();
	GAME_SPRITE_ANCHOR_ACCESSOR();

};
