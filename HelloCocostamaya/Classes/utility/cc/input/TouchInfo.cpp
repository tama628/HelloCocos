#include "TouchInfo.h"

#include "InputManager.h"

USING_NS_CC;

// コンストラクタ
TouchInfo::TouchInfo() :
m_id(ID_NULL),
m_status(TouchCode::TOUCH_NONE),
m_beginTime(0),
m_beginFlag(false),
m_moveFlag(false),
m_holdFlag(false),
m_endFlag(false),
m_pinchZoom(0)
{
}

// デストラクタ
TouchInfo::~TouchInfo()
{
}

// クリア
void TouchInfo::clear()
{
	m_id = ID_NULL;
	m_status = TouchCode::TOUCH_NONE;
	m_beginTime = 0;
	m_beginFlag = false;
	m_moveFlag = false;
	m_holdFlag = false;
	m_endFlag = false;
	m_pinchZoom = 0;
}

// 座標のログを取る
void TouchInfo::insertHistory( Touch *touch )
{
#if 0
	// UI座標
	Vec2 pt = touch->getLocationInView();
#else
	// GL座標
	Vec2 pt = touch->getLocation();
#endif
    // ログの制限
    int size = (int)m_touchHistory.size();
    if(size < m_touchHistory.capacity())
    {
        m_touchHistory.push_back( pt );
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            m_touchHistory[i-1] = m_touchHistory[i];
        }
        
        m_touchHistory[size-1] = pt;
        
        // CCLOG("TouchInfo::m_touchHistory Max !");
    }
    
    // CCLOG("move size=%lu", m_touchHistory.size());
}

// 始点と現在位置との座標差を取得
Vec2 TouchInfo::getTravel() const
{
	return this->getPosition() - this->getBeginPosition();
}

// 一つ前の座標と現在座標との差を取得
Vec2 TouchInfo::getPastTravel() const
{
	return this->getPosition() - this->getPastPosition();
}

// 始点と現在位置との距離を取得
float TouchInfo::getDistance() const
{
    return this->getBeginPosition().getDistance( this->getPosition() );
}

// 座標ヒストリーの合計距離を取得
float TouchInfo::getTotalDistance() const
{
    float totalDistance = 0.0f;
    int size = m_touchHistory.size();
    for(int i = 1; i < size; i++)
    {
        Vec2 pre = m_touchHistory[i-1];
        Vec2 cur = m_touchHistory[i];
        totalDistance += pre.getDistance( cur );
    }
    return totalDistance;
}

// 移動方向を取得
int TouchInfo::getDirection() const
{
	const auto &touch = GetTouchManager();
    return getDirection( touch.getMoveRange() );
}

// 移動方向を取得
int TouchInfo::getDirection( float correction_val ) const
{
    Vec2 start = m_touchHistory[0];
    Vec2 end = m_touchHistory.back();
    
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    
    int direction = 0;
    
    if( dx <= -correction_val )
    {
        direction |= DIRECTION_LEFT;
    }
    else if( correction_val <= dx )
    {
        direction |= DIRECTION_RIGHT;
    }
    
    if( dy <= -correction_val )
    {
		direction |= DIRECTION_DOWN;
    }
    else if( correction_val <= dy )
    {
        direction |= DIRECTION_UP;
    }
    
    return direction;
}

// 加速度を取得
float TouchInfo::getSpeed() const
{
    int size = m_touchHistory.size();
    if(1 < size)
    {
        return m_touchHistory.back().getDistance( m_touchHistory[size-2] );
    }
    return 0.0f;
}

// 現在位置を取得
Vec2 TouchInfo::getPosition() const
{
    if(0 < m_touchHistory.size())
    {
        return m_touchHistory.back();
    }
    return Vec2(0, 0);
}

// 一つ前の位置を取得
cocos2d::Vec2 TouchInfo::getPastPosition() const
{
    if(1 < m_touchHistory.size())
    {
        return m_touchHistory[m_touchHistory.size()-2];
    }
    return this->getPosition();
}

// 開始位置を取得
Vec2 TouchInfo::getBeginPosition() const
{
    return this->getTouchHistory(0);
}

// 移動時のログを取得
Vec2 TouchInfo::getTouchHistory(int index) const
{
	if(index < 0)
	{
		return this->getBeginPosition();
	}

    if(m_touchHistory.size() <= index)
    {
        return this->getPosition();
    }

    return m_touchHistory[index];
}

// 移動時のログ数を取得
int TouchInfo::getTouchHistorySize() const
{
    return m_touchHistory.size();
}
