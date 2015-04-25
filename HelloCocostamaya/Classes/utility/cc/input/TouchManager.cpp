#include "TouchManager.h"
#include "../GameUtility.h"

USING_NS_CC;

// 移動を感知する際の閾値
const float TouchManager::DEFAULT_MOVE_RANGE = 5.0f;
// ピンチを感知する際の閾値
const float TouchManager::DEFAULT_PINCH_RANGE = 24.0f;
// ダブルタップの有効時間
const unsigned long TouchManager::DEFAULT_DOUBLE_TAP_TIME = 300;
// 長押しになる時間
const unsigned long TouchManager::DEFAULT_HOLD_TIME = 300;
// スワイプになる時間
const unsigned long TouchManager::DEFAULT_SWIPE_TIME = 300;

TouchManager::TouchManager() :
m_pEventListener(nullptr)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
, m_mousePosition(0, 0)
#endif
{
}

TouchManager::~TouchManager()
{
}

void TouchManager::initialize()
{
	// フェイルセーフ
	this->finalize();

    // 入力用のパラメータ
    this->resetTouchParameter(true);
    
    // タッチの有効化
    // this->setTouchEnabled(true);

#if 0
    /* マルチタップ初期設定 */
    // マルチタップの有効化
    this->setMultiTapFlag(true);
    // 長押しの有効化
    this->setHoldFlag(true);
    // ドラッグの有効化
    this->setDragFlag(true);
    // スクロールの有効化
    this->setScrollFlag(true);
    // フリックの有効化
    this->setFlickFlag(true);
    // スワイプの有効化
    this->setSwipeFlag(true);
    // ピンチの有効化
    this->setPinchFlag(true);
#else
    /* シングルタップ初期設定 */
    // マルチタップの無効化
    this->setMultiTapFlag(false);
    // 長押しの有効化
    this->setHoldFlag(true);
    // ドラッグの有効化
    this->setDragFlag(true);
    // スクロールの有効化
    this->setScrollFlag(true);
    // フリックの有効化
    this->setFlickFlag(true);
    // スワイプの有効化
    this->setSwipeFlag(true);
    // ピンチの無効化
    this->setPinchFlag(false);
#endif

	// キー入力の設定
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto listener = EventListenerMouse::create();
	listener->onMouseDown  = CC_CALLBACK_1(TouchManager::onMouseDown, this);
	listener->onMouseMove  = CC_CALLBACK_1(TouchManager::onMouseMove, this);
	listener->onMouseScroll  = CC_CALLBACK_1(TouchManager::onMouseScroll, this);
	listener->onMouseUp  = CC_CALLBACK_1(TouchManager::onMouseUp, this);
	dispatcher->addEventListenerWithFixedPriority(listener, 1);
	m_pEventListener = listener;
#else
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan  = CC_CALLBACK_2(TouchManager::onTouchesBegan, this);
	listener->onTouchesMoved  = CC_CALLBACK_2(TouchManager::onTouchesMoved, this);
	listener->onTouchesEnded  = CC_CALLBACK_2(TouchManager::onTouchesEnded, this);
	listener->onTouchesCancelled  = CC_CALLBACK_2(TouchManager::onTouchesCancelled, this);
	dispatcher->addEventListenerWithFixedPriority(listener, 1);
	m_pEventListener = listener;
#endif
}

void TouchManager::finalize()
{
	// クリア
	this->clear();

	// 追加したリスナーをディスパッチャから削除する
	if( !m_pEventListener )
	{
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->removeEventListener(m_pEventListener);
		m_pEventListener = nullptr;
	}
}

void TouchManager::process(float delta)
{
	// シングルタップ判定
	this->checkSingleTap();

	// 長押し判定
	this->checkHold();
}

void TouchManager::lateProcess(float delta)
{
	// タッチ情報
	for( TouchInfo &touchInfo : m_infoArray )
	{
		// ステータスのリセット
		touchInfo.clearStatus();
	}
}

void TouchManager::clear()
{
    // 入力用のパラメータ
    this->resetTouchParameter();
}

void TouchManager::resetTouchParameter(bool allResetFlag)
{
    if(allResetFlag)
    {
        m_multiTapFlag = false;
        m_holdFlag = false;
        m_dragFlag = false;
        m_scrollFlag = false;
        m_flickFlag = false;
        m_swipeFlag = false;
        m_pinchFlag = false;
        
        m_moveRange = DEFAULT_MOVE_RANGE;
        m_pinchRange = DEFAULT_PINCH_RANGE;
        m_doubleTapTime = DEFAULT_DOUBLE_TAP_TIME;
        m_holdTime = DEFAULT_HOLD_TIME;
        m_swipeTime = DEFAULT_SWIPE_TIME;
    }
    
	// ステータスのリセット
	for( TouchInfo &touchInfo : m_infoArray )
	{
		touchInfo.clear();
	}
    
    m_checkDoubleTapFlag = false;
    m_checkDoubleTapTime = 0;
    
    m_firstTapID = TouchInfo::ID_NULL;
    m_firstTapPoint = Vec2::ZERO;
    m_firstTapTime = 0;
    
    m_baseDistanceOfPinch = 0;
    m_previousDidstanceOfPinch = 0;
    m_touchIDForPinch[0] = TouchInfo::ID_NULL;
    m_touchIDForPinch[1] = TouchInfo::ID_NULL;
    m_pinchStartFlag = false;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void TouchManager::onMouseDown(Event *pEvent)
{
	// マウスのときもタッチと同等の処理をしたいのでCCTouchを作成しそれをタッチ関数に渡す
	EventMouse *pEventMouse = static_cast<EventMouse*>(pEvent);
    // CCLOG("TouchManager::onMouseDown() / button = %d, x = %f, y = %f", pEventMouse->getMouseButton(), pEventMouse->getCursorX(), pEventMouse->getCursorY());

	auto director = Director::getInstance();
	Point uiPoint = director->convertToUI( ccp(pEventMouse->getCursorX(), pEventMouse->getCursorY()) );

	Touch touch;
	touch.setTouchInfo(0, uiPoint.x, uiPoint.y);
	CCLOG("TouchManager::onMouseDown() / viewX = %f, viewY = %f", touch.getLocation().x, touch.getLocation().y);

	std::vector<Touch*> touches;
	touches.push_back( &touch );

	this->onTouchesBegan(touches, pEvent);
}

void TouchManager::onMouseMove(Event *pEvent)
{
	// マウスのときもタッチと同等の処理をしたいのでCCTouchを作成しそれをタッチ関数に渡す
	EventMouse *pEventMouse = static_cast<EventMouse*>(pEvent);
    // CCLOG("TouchManager::onMouseMove() / button = %d, x = %f, y = %f", pEventMouse->getMouseButton(), pEventMouse->getCursorX(), pEventMouse->getCursorY());

	auto director = Director::getInstance();
	Point uiPoint = director->convertToUI( ccp(pEventMouse->getCursorX(), pEventMouse->getCursorY()) );

	Touch touch;
	touch.setTouchInfo(0, uiPoint.x, uiPoint.y);
	// CCLOG("TouchManager::onMouseMove() / viewX = %f, viewY = %f", touch.getLocation().x, touch.getLocation().y);

	// マウス座標
	m_mousePosition = touch.getLocation();

	if( m_infoArray[0].getEndFlag() || !m_infoArray[0].getBeginFlag() )
	{
		return;
	}

	std::vector<Touch*> touches;
	touches.push_back( &touch );

	this->onTouchesMoved(touches, pEvent);
}

void TouchManager::onMouseScroll(Event *pEvent)
{
}

void TouchManager::onMouseUp(Event *pEvent)
{
	// マウスのときもタッチと同等の処理をしたいのでCCTouchを作成しそれをタッチ関数に渡す
	EventMouse *pEventMouse = static_cast<EventMouse*>(pEvent);
    // CCLOG("TouchManager::onMouseUp() / button = %d, x = %f, y = %f", pEventMouse->getMouseButton(), pEventMouse->getCursorX(), pEventMouse->getCursorY());

	auto director = Director::getInstance();
	Point uiPoint = director->convertToUI( ccp(pEventMouse->getCursorX(), pEventMouse->getCursorY()) );

	Touch touch;
	touch.setTouchInfo(0, uiPoint.x, uiPoint.y);
	// CCLOG("TouchManager::onMouseUp() / viewX = %f, viewY = %f", touch.getLocation().x, touch.getLocation().y);

	std::vector<Touch*> touches;
	touches.push_back( &touch );

	this->onTouchesEnded(touches, pEvent);
}
#endif

void TouchManager::onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent)
{
    // CCLOG( "TouchManager::onTouchesBegan() count=%d", touches.size() );
    
    // タッチ判定
    unsigned int currentTime = GameUtility::getTimeByMilliSecond();
	for( Touch *pTouch : touches )
    {
        int id = pTouch->getID();
		if( TOUCH_MAX <= id ) continue;

		// シングルタップのための対応
		if( !m_multiTapFlag && id != 0 )
		{
			continue;
		}

        // information
        TouchInfo touchInfo;
		touchInfo.setID( id );
        touchInfo.setBeginTime( currentTime );
		touchInfo.setBeginFlag( true );
		touchInfo.insertHistory( pTouch );
		touchInfo.setStatus( TouchCode::TOUCH_DOWN );
		m_infoArray[id] = touchInfo;
        
        // pinch
        this->checkPinch( pTouch );
    }
}

void TouchManager::onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent)
{
	// CCLOG( "TouchManager::onTouchesMoved() count=%d", touches.size() );

    // タッチ判定
	for( Touch *pTouch : touches )
    {
        int id = pTouch->getID();
        
		// シングルタップのための対応
		if( !m_multiTapFlag && id != 0 )
		{
			continue;
		}
        
        // information
        TouchInfo *pTouchInfo = this->getMutableTouchInfo(id);
        if(pTouchInfo == NULL)
        {
            continue;
        }
        
        // insert history
        pTouchInfo->insertHistory( pTouch );
        
        // check move
        if( !pTouchInfo->getMoveFlag() )
        {
            // 一定以上移動したらmoveフラグをtrueにする
            float distance = pTouchInfo->getDistance();
            if(distance >= m_moveRange)
            {
                pTouchInfo->setMoveFlag( true );
            }
        }
        
        // pinch action
        if( !this->checkPinch(pTouch) )
        {
            // moveフラグがtrueのとき
            if( pTouchInfo->getMoveFlag() )
            {
				pTouchInfo->addStatus( TouchCode::TOUCH_MOVE );
                if( pTouchInfo->getHoldFlag() )
                {
                    // ホールド時はドラッグ
                    if(m_dragFlag)
                    {
						pTouchInfo->addStatus( TouchCode::TOUCH_DRAG );
                    }
                }
                else
                {
                    // ホールドされていないときはスクロール
                    if(m_scrollFlag)
                    {
						pTouchInfo->addStatus( TouchCode::TOUCH_SCROLL );
                    }
                }
            }
        }
    }
}

void TouchManager::onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent)
{
	// CCLOG( "TouchManager::onTouchesEnded() count=%d", touches.size() );
    
    // タッチ判定
    unsigned int currentTime = GameUtility::getTimeByMilliSecond();
	for( Touch *pTouch : touches )
    {
        int id = pTouch->getID();
        
		// シングルタップのための対応
		if( !m_multiTapFlag && id != 0 )
		{
			continue;
		}
        
        // information
        TouchInfo *pTouchInfo = this->getMutableTouchInfo(id);
        if(pTouchInfo == NULL)
        {
            continue;
        }
        
        // insert history
        // pTouchInfo->insertHistory( pTouch );
        
        // end flag
        pTouchInfo->setEndFlag( true );
        
        // callback
        if( pTouchInfo->getHoldFlag() )
        {
            if (m_dragFlag)
            {
				pTouchInfo->addStatus( TouchCode::TOUCH_DRAG_END );
            }
        }
        else if( this->checkPinch(pTouch, true) )
        {
            // pinch
        }
        else if( pTouchInfo->getMoveFlag() )
        {
            // check time
            unsigned int scroll_time = currentTime - pTouchInfo->getBeginTime();
            
            // slide end
            if( scroll_time < m_swipeTime )
            {
                if(m_flickFlag)
                {
					pTouchInfo->addStatus( TouchCode::TOUCH_FLICK );
                }
            }
            else
            {
                if(m_swipeFlag)
                {
					pTouchInfo->addStatus( TouchCode::TOUCH_SWIPE );
                }
            }
        }
        else
        {
			pTouchInfo->addStatus( TouchCode::TOUCH_TAP );
            this->tapEvent( pTouch );
        }
    }
}

void TouchManager::onTouchesCancelled(const std::vector<Touch*>& touches, Event *pEvent)
{
	// CCLOG( "TouchManager::onTouchesCancelled() count=%d", touches.size() );
    
    // タッチ判定
	for( Touch *pTouch : touches )
    {
        int id = pTouch->getID();
        
        // シングルタップのための対応
		if( !m_multiTapFlag && id != 0 )
        {
            continue;
        }
        
        // information
        TouchInfo *pTouchInfo = this->getMutableTouchInfo(id);
        if(pTouchInfo == NULL)
        {
            continue;
        }
        
        // insert history
        // pTouchInfo->insertHistory( pTouch );
        
        // end flag
        pTouchInfo->setEndFlag( true );
        
        // callback
		pTouchInfo->addStatus( TouchCode::TOUCH_CANCELL );
    }
}

void TouchManager::checkSingleTap()
{
    // ダブルタップ判定中か
    if(m_checkDoubleTapFlag)
    {
        // ダブルタップ判定の時間を過ぎたか
        unsigned long elapsedTime = GameUtility::getTimeByMilliSecond() - m_checkDoubleTapTime;
        if(elapsedTime > m_doubleTapTime)
        {
            // シングルタップ
            if(m_firstTapID < 0) return;
            
            TouchInfo *pTouchInfo = this->getMutableTouchInfo(m_firstTapID);
            if( pTouchInfo != NULL )
            {
				pTouchInfo->addStatus( TouchCode::TOUCH_SINGLE_TAP );
            }
            m_firstTapID = TouchInfo::ID_NULL;
            m_firstTapTime = 0;
            m_firstTapPoint = Vec2::ZERO;
            
            // 終了
            m_checkDoubleTapFlag = false;
        }
    }
}

void TouchManager::checkHold()
{
	for( TouchInfo &touchInfo : m_infoArray )
    {
        int touchID = touchInfo.getID();
		if( touchID == TouchInfo::ID_NULL || touchInfo.getEndFlag() ) continue;

		// press
		touchInfo.addStatus( TouchCode::TOUCH_PRESS );

        if( touchInfo.getMoveFlag() || touchInfo.getHoldFlag() )
        {
            continue;
        }
        
        // pinch
        if( m_touchIDForPinch[0] != TouchInfo::ID_NULL && m_touchIDForPinch[1] != TouchInfo::ID_NULL )
        {
            if( m_touchIDForPinch[0] == touchID || m_touchIDForPinch[1] == touchID )
            {
                continue;
            }
        }
        
        unsigned long elapsedTime = GameUtility::getTimeByMilliSecond() - touchInfo.getBeginTime();
        if (elapsedTime >= m_holdTime)
        {
            touchInfo.setHoldFlag( true );
			touchInfo.addStatus( TouchCode::TOUCH_HOLD );
        }
    }
}

bool TouchManager::checkPinch(Touch *pTouch, bool endFlag)
{
    // ピンチフラグ
    if(!m_pinchFlag) return false;
    
    int id = pTouch->getID();
      
    // タッチ中か
	if( !endFlag )
	{
		// タッチ中
		bool newFlag = false;
		bool checkFlag = true;
		if( m_touchIDForPinch[0] != id && m_touchIDForPinch[1] != id )
		{
			// id設定
			if( m_touchIDForPinch[0] == TouchInfo::ID_NULL ) {
				m_touchIDForPinch[0] = id;
				newFlag = true;
			}
			else if( m_touchIDForPinch[1] == TouchInfo::ID_NULL ) {
				m_touchIDForPinch[1] = id;
				newFlag = true;
			}
			else {
				checkFlag = false;
			}
		}

		// check two finger.
		if( checkFlag && m_touchIDForPinch[0] != TouchInfo::ID_NULL && m_touchIDForPinch[1] != TouchInfo::ID_NULL )
		{
			// alias
			int id2 = m_touchIDForPinch[0];
			int id3 = m_touchIDForPinch[1];
			TouchInfo *pTouchInfo2 = this->getMutableTouchInfo(id2);
			TouchInfo *pTouchInfo3 = this->getMutableTouchInfo(id3);

			// failsafe
			if( pTouchInfo2 != NULL && pTouchInfo3 != NULL )
			{
				// point
				CCPoint pt2 = pTouchInfo2->getPosition();
				CCPoint pt3 = pTouchInfo3->getPosition();
				float distance = fabsf(pt2.getDistance(pt3));

				// if there is a new registration, calculate base distance.
				if( newFlag )
				{
					m_previousDidstanceOfPinch = distance;
					m_baseDistanceOfPinch = distance;
				}

				// get magnification
				float zoom = 1.0f;
				if( m_baseDistanceOfPinch != 0.0f )
				{
					// ズーム値の計算(始点の２点間の距離を1.0として割合を計算する)
					zoom = distance / m_baseDistanceOfPinch;

					// ピンチ処理を開始していない
					if( !m_pinchStartFlag )
					{
						// 遊びを持たせる
						float moveDistance = distance - m_baseDistanceOfPinch;
						CCLOG("pt2=%f,%f pt3=%f,%f", pt2.x, pt2.y, pt3.x, pt3.y);
						CCLOG("distance=%f, base=%f, move=%f", distance, m_baseDistanceOfPinch, moveDistance);
						if( moveDistance <= -m_pinchRange || m_pinchRange <= moveDistance )
						{
							// ピンチ処理を開始する
							m_pinchStartFlag = true;
						}
					}
				}

				// ピンチ処理を開始している
				if( m_pinchStartFlag )
				{
					// callback
					pTouchInfo2->addStatus(TouchCode::TOUCH_PINCH);
					pTouchInfo3->addStatus(TouchCode::TOUCH_PINCH);
					if( distance < m_previousDidstanceOfPinch )
					{
						pTouchInfo2->addStatus(TouchCode::TOUCH_PINCH_IN);
						pTouchInfo3->addStatus(TouchCode::TOUCH_PINCH_IN);
					}
					else if( distance > m_previousDidstanceOfPinch )
					{
						pTouchInfo2->addStatus(TouchCode::TOUCH_PINCH_OUT);
						pTouchInfo3->addStatus(TouchCode::TOUCH_PINCH_OUT);
					}

					// ズーム値を設定
					pTouchInfo2->setPinchZoom(zoom);
					pTouchInfo3->setPinchZoom(zoom);
				}

				m_previousDidstanceOfPinch = distance;

				return true;
			}
		}
	}
	else
    {
		// タッチ終了
        int id2 = m_touchIDForPinch[0];
        int id3 = m_touchIDForPinch[1];

        int index = id == id2 ? 0 : id == id3 ? 1 : TouchInfo::ID_NULL;
        if(index != TouchInfo::ID_NULL)
        {
            if ( m_pinchStartFlag )
            {
                // callback
                if(id2 != TouchInfo::ID_NULL && id3 != TouchInfo::ID_NULL)
                {
                    TouchInfo *pTouchInfo2 = this->getMutableTouchInfo(id2);
                    TouchInfo *pTouchInfo3 = this->getMutableTouchInfo(id3);
                        
                    // failsafe
                    if(pTouchInfo2 != NULL && pTouchInfo3 != NULL)
                    {
                        CCPoint pt2 = pTouchInfo2->getPosition();
                        CCPoint pt3 = pTouchInfo3->getPosition();
                            
                        float distance = fabsf( pt2.getDistance(pt3) );
                        float zoom = 1.0f;
                        if(m_baseDistanceOfPinch != 0.0f)
                        {
							// ズーム値の計算(始点の２点間の距離を1.0として割合を計算する)
                            zoom = distance / m_baseDistanceOfPinch;
                        }
                            
                        // callback
						pTouchInfo2->addStatus( TouchCode::TOUCH_PINCH_END );
						pTouchInfo3->addStatus( TouchCode::TOUCH_PINCH_END );

						// ズーム値を設定
						pTouchInfo2->setPinchZoom( zoom );
						pTouchInfo3->setPinchZoom( zoom );
                    }
                }
            }
                
            // reset
            m_baseDistanceOfPinch = 0;
            m_previousDidstanceOfPinch = 0;
            m_touchIDForPinch[index] = TouchInfo::ID_NULL;
            m_pinchStartFlag = false;
        }
    }
    
    return false;
}

void TouchManager::tapEvent(Touch *pTouch)
{
    // stop singletap handler
    // this->unschedule( schedule_selector(InterfaceLayer::scheduleSingleTapHandler) );
    m_checkDoubleTapFlag = false;
    
    // check double tap
	int id = pTouch->getID();
	if( id == m_firstTapID )
	{
		// check tap interval
		int interval = GameUtility::getTimeByMilliSecond() - m_firstTapTime;
		if( interval <= m_doubleTapTime )
		{
			// double tap
			TouchInfo *pTouchInfo = this->getMutableTouchInfo(id);
			if( pTouchInfo != NULL )
			{
				pTouchInfo->addStatus(TouchCode::TOUCH_DOUBLE_TAP);
			}

			// reset
			m_firstTapID = TouchInfo::ID_NULL;
			m_firstTapTime = 0;
			m_firstTapPoint = Vec2::ZERO;

			// return
			return;
		}

	}
    
    // setup
    m_firstTapID = pTouch->getID();
    m_firstTapTime = GameUtility::getTimeByMilliSecond();
    m_firstTapPoint = pTouch->getLocation();
    
    // start a schedule for the SingleTap Callback;
    // this->scheduleOnce(schedule_selector(InterfaceLayer::scheduleSingleTapHandler), DOUBLE_TAP_TIME);
    m_checkDoubleTapFlag = true;
    m_checkDoubleTapTime = GameUtility::getTimeByMilliSecond();
}
