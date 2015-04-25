#include "GameLabel.h"

USING_NS_CC;

GameLabel::GameLabel(FontAtlas *atlas, TextHAlignment hAlignment, 
        TextVAlignment vAlignment,bool useDistanceField,bool useA8Shader) :
Label(atlas, hAlignment, vAlignment, useDistanceField, useA8Shader)
{
}

void GameLabel::defaultSetting()
{
	this->setPosition( Vec2(0,0) );
	this->setAnchorPoint( Vec2(0,0) );
}

GameLabel* GameLabel::create(const char *fontName, float fontSize,
                             const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    if (FileUtils::getInstance()->isFileExist(fontName))
    {
        return createWithTTF(fontName,fontSize,dimensions,hAlignment,vAlignment);
    } 
    else
    {
        return createWithSystemFont(fontName,fontSize,dimensions,hAlignment,vAlignment);
    }
}

GameLabel* GameLabel::createWithSystemFont(const char * font, float fontSize,
										   const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    auto ret = new(std::nothrow) GameLabel(nullptr,hAlignment,vAlignment);

    if (ret)
    {
        ret->setSystemFontName(font);
        ret->setSystemFontSize(fontSize);
        ret->setDimensions(dimensions.width, dimensions.height);
        // ret->setString(text);

		ret->defaultSetting();
        ret->autorelease();

        return ret;
    }

    delete ret;
    return nullptr;
}

GameLabel* GameLabel::createWithTTF(const char * fontFile, float fontSize,
									const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    auto ret = new(std::nothrow) GameLabel(nullptr,hAlignment,vAlignment);

    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig ttfConfig(fontFile,fontSize,GlyphCollection::DYNAMIC);
        if (ret->setTTFConfig(ttfConfig))
        {
            ret->setDimensions(dimensions.width,dimensions.height);
            // ret->setString(text);

			ret->defaultSetting();
            ret->autorelease();

            return ret;
        }
    }

    delete ret;
    return nullptr;
}
