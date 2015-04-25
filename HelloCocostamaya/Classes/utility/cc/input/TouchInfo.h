#pragma once
#include "cocos2d.h"
#include "utility/data/Array.h"

class TouchInfo {
    
public:
    
    // 移動時のログの最大保持数
    static const int TOUCH_HISTORY_MAX = 60;
    
    // タッチID
    enum ID
    {
        ID_NULL = -1
    };

	// ステータス
	typedef int status_t;
	enum TouchCode : status_t
	{
		TOUCH_NONE,
		TOUCH_SINGLE_TAP		= 1 << 0,
		TOUCH_DOUBLE_TAP		= 1 << 1,
		TOUCH_DOWN				= 1 << 2,
		TOUCH_HOLD				= 1 << 3,
		TOUCH_CANCELL			= 1 << 4,
		TOUCH_MOVE				= 1 << 5,
		TOUCH_SCROLL			= 1 << 6,
		TOUCH_DRAG				= 1 << 7,
		TOUCH_FLICK				= 1 << 8,
		TOUCH_SWIPE				= 1 << 9,
		TOUCH_DRAG_END			= 1 << 10,
		TOUCH_TAP				= 1 << 11,
		TOUCH_PINCH_IN			= 1 << 12,
		TOUCH_PINCH_OUT			= 1 << 13,
		TOUCH_PINCH				= 1 << 14,
		TOUCH_PINCH_END			= 1 << 15,
		TOUCH_PRESS				= 1 << 16
	};
    
    // 移動時の向き
    enum DIRECTION
    {
        DIRECTION_UP = 1 << 0,
        DIRECTION_DOWN = 1 << 1,
        DIRECTION_LEFT = 1 << 2,
        DIRECTION_RIGHT = 1 << 3
    };

	// コンストラクタ
	TouchInfo();
	// デストラクタ
	~TouchInfo();
    
	// クリア
	void clear();
    // 座標のログを取る
    void insertHistory( cocos2d::Touch *touch );
    
	// 始点と現在位置との座標差を取得
	cocos2d::Vec2 getTravel() const;
	// 一つ前の座標と現在座標との差を取得
	cocos2d::Vec2 getPastTravel() const;
    // 始点と現在位置との距離を取得
    float getDistance() const;
    // 座標ヒストリーの合計移動距離を取得
    float getTotalDistance() const;
    // 移動方向を取得
    int getDirection() const;
    // 移動方向を取得
    int getDirection( float correction_val ) const;
    // 加速度を取得
    float getSpeed() const;
    // 現在位置を取得
    cocos2d::Vec2 getPosition() const;
	// 一つ前の位置を取得
	cocos2d::Vec2 getPastPosition() const;
    // 開始位置を取得
    cocos2d::Vec2 getBeginPosition() const;
    // 移動時のログを取得
    cocos2d::Vec2 getTouchHistory(int index) const;
    // 移動時のログ数を取得
    int getTouchHistorySize() const;
    
    // タッチIDの取得
    int getID() const { return m_id; }
    // タッチIDの設定
    void setID(int id) { m_id = id; }
    // タッチ開始時の時間を取得
    unsigned long getBeginTime() const { return m_beginTime; }
    // タッチ開始時の時間を設定
    void setBeginTime(unsigned long beginTime) { m_beginTime = beginTime; }
    // タッチ開始かのフラグを取得
    bool getBeginFlag() const { return m_beginFlag; }
    // タッチ開始かのフラグを設定
    void setBeginFlag(bool flag) { m_beginFlag = flag; }
    // 移動中かのフラグを取得
    bool getMoveFlag() const { return m_moveFlag; }
    // 移動中かのフラグを設定
    void setMoveFlag(bool flag) { m_moveFlag = flag; }
    // 長押し中かのフラグを取得
    bool getHoldFlag() const { return m_holdFlag; }
    // 長押し中かのフラグを設定
    void setHoldFlag(bool flag) { m_holdFlag = flag; }
    // タッチ終了かのフラグを取得
    bool getEndFlag() const { return m_endFlag; }
    // タッチ終了かのフラグを設定
    void setEndFlag(bool flag) { m_endFlag = flag; }

	// ステータスの取得
	status_t getStatus() const { return m_status; }
	// ステータスの設定
	void setStatus(status_t status) { m_status = status; }
	// ステータスの追加
	void addStatus(status_t status) { m_status |= status; }
	// ステータスのクリア
	void clearStatus() { m_status = TouchCode::TOUCH_NONE; m_pinchZoom = 0; }

	// ピンチ時のズーム値を取得
	float getPinchZoom() const { return m_pinchZoom; }
	// ピンチ時のズーム値を設定
	void setPinchZoom(float value) { m_pinchZoom = value; }
   
private:
    
    // タッチID
    int m_id;
	// ステータス
	status_t m_status;
    // タッチ開始時の時間
    unsigned long m_beginTime;
	// タッチ開始かのフラグ
	bool m_beginFlag;
    // 移動中かのフラグ
    bool m_moveFlag;
    // 長押し中かのフラグ
    bool m_holdFlag;
    // タッチが有効かのフラグ
    bool m_endFlag;
    // タッチ座標の履歴
   FixedSizeArray<cocos2d::Vec2, TOUCH_HISTORY_MAX> m_touchHistory;

   // ピンチ時のズーム値(始点の２点間の距離を1.0として割合を計算する)
   float m_pinchZoom;
    
};
