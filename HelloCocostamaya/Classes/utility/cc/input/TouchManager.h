#pragma once
#include "TouchInfo.h"

typedef TouchInfo::TouchCode TouchCode;
class TouchManager {

	explicit TouchManager( const TouchManager& );

public:

	// タッチ数
	static const int TOUCH_MAX = 4;

	// 移動を感知する際の閾値
	static const float DEFAULT_MOVE_RANGE;
	// ピンチを感知する際の閾値
	static const float DEFAULT_PINCH_RANGE;
	// ダブルタップの有効時間
	static const unsigned long DEFAULT_DOUBLE_TAP_TIME;
	// 長押しになる時間
	static const unsigned long DEFAULT_HOLD_TIME;
	// スワイプになる時間
	static const unsigned long DEFAULT_SWIPE_TIME;

public:

	TouchManager();
	~TouchManager();

	void initialize();
	void finalize();
	void process(float delta);
	void lateProcess(float delta);
	void clear();
	void resetTouchParameter(bool allResetFlag = false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void onMouseDown(cocos2d::Event *pEvent);
	void onMouseMove(cocos2d::Event *pEvent);
	void onMouseScroll(cocos2d::Event *pEvent);
	void onMouseUp(cocos2d::Event *pEvent);
#endif

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
	void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);

	// マルチタップ有効フラグの設定
	void setMultiTapFlag(bool value);
	// 長押し有効フラグの設定
	void setHoldFlag(bool value);
	// ドラッグ有効フラグの設定
	void setDragFlag(bool value);
	// スクロール有効フラグの設定
	void setScrollFlag(bool value);
	// フリック有効フラグの設定
	void setFlickFlag(bool value);
	// スワイプ有効フラグの設定
	void setSwipeFlag(bool value);
	// ピンチ有効フラグの設定
	void setPinchFlag(bool value);
    
	// 移動を感知する際の閾値を取得
	float getMoveRange() const;
	// 移動を感知する際の閾値を設定
	void setMoveRange(float value);
	// ピンチを感知する際の閾値を取得
	float getPinchRange() const;
	// ピンチを感知する際の閾値を設定
	void setPinchRange(float value);
	// ダブルタップの有効時間を取得
	unsigned long getDoubleTapTime(unsigned long msec) const;
	// ダブルタップの有効時間を設定
	void setDoubleTapTime(unsigned long msec);
	// 長押しになる時間を取得
	unsigned long getHoldTime() const;
	// 長押しになる時間を設定
	void setHoldTime(unsigned long msec);
	// スワイプになる時間を取得
	unsigned long getSwipeTime() const;
	// スワイプになる時間を設定
	void setSwipeTime(unsigned long msec);

	// タッチイベントが発生したか
	bool isTrigger(int id = 0) const { return m_infoArray[id].getStatus() != TouchCode::TOUCH_NONE; }
	// タッチの状態を取得
	bool isGesture(TouchCode touchCode, int id = 0) const { return (m_infoArray[id].getStatus() & touchCode) != 0; }
	// idからTouchInfoを取得する
	const TouchInfo *getTouchInfo(int id = 0) const;

	// マウス座標を取得する(CC_PLATFORM_WIN32)
	cocos2d::Vec2 getMousePosition() const { return m_mousePosition; }
    
private:
    
	// idからTouchInfoを取得する
	TouchInfo *getMutableTouchInfo(int id);

private:

	// シングルタップ判定
	void checkSingleTap();
	// ホールド判定
	void checkHold();
	// ピンチ判定
	bool checkPinch(cocos2d::Touch *pTouch, bool is_end = false);
	// onTap()時の処理
	void tapEvent(cocos2d::Touch *pTouch);
	// idからタッチ
	float getDistanceBetweenTwoTouch(int id, int id2);

private:

	cocos2d::EventListener *m_pEventListener;

	// マルチタップ有効フラグ
	bool m_multiTapFlag;
	// 長押し有効フラグ
	bool m_holdFlag;
	// ドラッグ有効フラグ
	bool m_dragFlag;
	// スクロール有効フラグ
	bool m_scrollFlag;
	// フリック有効フラグ
	bool m_flickFlag;
	// スワイプ有効フラグ
	bool m_swipeFlag;
	// ピンチアクション有効フラグ(マルチタップ有効時)
	bool m_pinchFlag;
	// 移動を感知する際の遊び
	float m_moveRange;
	// ピンチを感知する際の遊び
	float m_pinchRange;
	// ダブルタップの有効時間(msec)
	unsigned long m_doubleTapTime;
	// 長押しになる時間(msec)
	unsigned long m_holdTime;
	// スワイプになる時間(msec)
	unsigned long m_swipeTime;
	// ダブルタップ判定中か
	bool m_checkDoubleTapFlag;
	// ダブルタップかを判定するための時間保持用
	unsigned long m_checkDoubleTapTime;
	// 最初にタップしたときの情報
	int m_firstTapID;
	cocos2d::Vec2 m_firstTapPoint;
	unsigned long m_firstTapTime;
	// ピンチ用の情報
	float m_baseDistanceOfPinch;
	float m_previousDidstanceOfPinch;
	int m_touchIDForPinch[2];
	bool m_pinchStartFlag;

	// タッチ情報の格納用
	TouchInfo m_infoArray[ TOUCH_MAX ];

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// マウス座標(CC_PLATFORM_WIN32)
	cocos2d::Vec2 m_mousePosition;
#endif

};

inline void TouchManager::setMultiTapFlag( bool value )
{
    m_multiTapFlag = value;

    // パラメータのリセット
    this->resetTouchParameter();
}

inline void TouchManager::setHoldFlag(bool value)
{
    m_holdFlag = value;
}

inline void TouchManager::setDragFlag(bool value)
{
    m_dragFlag = value;
}

inline void TouchManager::setScrollFlag(bool value)
{
    m_scrollFlag = value;
}

inline void TouchManager::setFlickFlag(bool value)
{
    m_flickFlag = value;
}

inline void TouchManager::setSwipeFlag(bool value)
{
    m_swipeFlag = value;
}

inline void TouchManager::setPinchFlag(bool value)
{
    m_pinchFlag = value;
}

inline float TouchManager::getMoveRange() const
{
    return m_moveRange;
}

inline void TouchManager::setMoveRange(float value)
{
    m_moveRange = value;
}

inline float TouchManager::getPinchRange() const
{
    return m_pinchRange;
}

inline void TouchManager::setPinchRange(float value)
{
    m_pinchRange = value;
}

inline unsigned long TouchManager::getDoubleTapTime(unsigned long msec) const
{
    return m_doubleTapTime;
}

inline void TouchManager::setDoubleTapTime(unsigned long msec)
{
    m_doubleTapTime = msec;
}

inline unsigned long TouchManager::getHoldTime() const
{
    return m_holdTime;
}

inline void TouchManager::setHoldTime(unsigned long msec)
{
    m_holdTime = msec;
}

inline unsigned long TouchManager::getSwipeTime() const
{
    return m_swipeTime;
}

inline void TouchManager::setSwipeTime(unsigned long msec)
{
    m_swipeTime = msec;
}

inline const TouchInfo *TouchManager::getTouchInfo(int id) const
{
	if( id < TOUCH_MAX )
	{
		return &m_infoArray[id];
	}
	return NULL;
}

inline TouchInfo *TouchManager::getMutableTouchInfo(int id)
{
	if( id < TOUCH_MAX )
	{
		return &m_infoArray[id];
	}
	return NULL;
}
