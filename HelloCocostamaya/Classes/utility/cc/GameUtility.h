#pragma once
#include "cocos2d.h"
#include "../type.h"

namespace GameUtility {

	// ノードのローカル座標をワールド座標に変換して取得する
	cocos2d::Vec2 localToWorldPosition( const cocos2d::Node *pNode );
	// 時間の取得(msec)
    clock_t getTimeByMilliSecond();
    // 文字列の置換
	void grep( std::string &str, const char *src, const char *dst );
	// 当たり判定
	bool isHit( const cocos2d::Vec2 &point, const cocos2d::Node *pNode );
	// 当たり判定
	bool isHit( float pointX, float pointY, float x, float y, float width, float height );

	// クランプ
	template< typename type > type clamp( type value, type low, type high )
	{
		return ((low <= value) ? ((high < value) ? high : value) : low);
	}
	// 解放処理
	template< typename type > type safeRelease( type *&pValue )
	{
		delete pValue;
		pValue = nullptr;
	}
	// degreeをradianへ変換
	static float degreeToRadian(float degree)
	{
		return degree * M_PI / 180.0f;
	}
	// radianをdegreeへ変換
	static float radianToDegree(float radian)
	{
		return radian * 180.0f / M_PI;
	}

} // namespace GameUtility
