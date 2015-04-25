#include "KeyManager.h"

USING_NS_CC;

KeyManager::KeyManager() :
m_pEventListener(nullptr),
m_triggerFlag(false)
{
	memset(&m_keyInfoArray, 0, sizeof(KeyInfoArray));
	memset(&m_keyInfoArrayLog, 0, sizeof(KeyInfoArray) * KEY_INFO_LOG);
}

KeyManager::~KeyManager()
{
}

void KeyManager::initialize()
{
	// フェイルセーフ
	this->finalize();
	
	// フラグの設定
	m_triggerFlag = false;

	// キー入力の設定
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(KeyManager::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(KeyManager::onKeyReleased, this);
	dispatcher->addEventListenerWithFixedPriority(listener, 1);
	m_pEventListener = listener;
}

void KeyManager::finalize()
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

void KeyManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	// CCLOG("KeyManager::onKeyPressed / keyCode=%d", keyCode);

	int code = static_cast<int>( keyCode );
	if(code < KEY_INFO_MAX)
	{
		KeyInfo *pKeyInfo = &m_keyInfoArray[code];
		pKeyInfo->status = 0;
		pKeyInfo->status |= STATUS_PUSH;
		pKeyInfo->status |= STATUS_PRESS;
		pKeyInfo->status |= STATUS_PRESS_REPEAT;
		pKeyInfo->status |= STATUS_PRESS_REPEATFAST;
		pKeyInfo->frame = 0;
		pKeyInfo->repeatCount = 0;
		pKeyInfo->repeatFastCount = 0;
	}
}

void KeyManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	// CCLOG("KeyManager::onKeyReleased / keyCode=%d", keyCode);

	int code = static_cast<int>( keyCode );
	if(code < KEY_INFO_MAX)
	{
		KeyInfo *pKeyInfo = &m_keyInfoArray[code];
		pKeyInfo->status = 0;
		pKeyInfo->status |= STATUS_PULL;
		pKeyInfo->status |= STATUS_FREE;
		pKeyInfo->status |= STATUS_FREE_REPEAT;
		pKeyInfo->status |= STATUS_FREE_REPEATFAST;
		pKeyInfo->frame = 0;
		pKeyInfo->repeatCount = 0;
		pKeyInfo->repeatFastCount = 0;
	}
}

void KeyManager::process(float delta)
{
	// フラグの設定
	m_triggerFlag = false;

	// 更新
	for(int i = 0; i < KEY_INFO_MAX; i++)
	{
		KeyInfo *pKeyInfo = &m_keyInfoArray[i];

		if( 0 < pKeyInfo->frame )
		{
			if( pKeyInfo->status & STATUS_PRESS )
			{
				pKeyInfo->status = STATUS_PRESS;

				// キーリピート開始
				if(REPEAT_START <= pKeyInfo->frame)
				{
					// キーリピート
					if(--(pKeyInfo->repeatCount) < 0)
					{
						pKeyInfo->status |= STATUS_PRESS_REPEAT;
						pKeyInfo->repeatCount = REPEAT_SPAN;
					}

					// キーリピートファスト
					if(--(pKeyInfo->repeatFastCount) < 0)
					{
						pKeyInfo->status |= STATUS_PRESS_REPEATFAST;
						pKeyInfo->repeatFastCount = REPEATFAST_SPAN;
					}						
				}
			}
			else if( pKeyInfo->status & STATUS_FREE )
			{
				pKeyInfo->status = STATUS_FREE;

				// キーリピート開始
				if(REPEAT_START <= pKeyInfo->frame)
				{
					// キーリピート
					if(--(pKeyInfo->repeatCount) < 0)
					{
						pKeyInfo->status |= STATUS_FREE_REPEAT;
						pKeyInfo->repeatCount = REPEAT_SPAN;
					}

					// キーリピートファスト
					if(--(pKeyInfo->repeatFastCount) < 0)
					{
						pKeyInfo->status |= STATUS_FREE_REPEATFAST;
						pKeyInfo->repeatFastCount = REPEATFAST_SPAN;
					}
				}
			}
		}
		else
		{
			// トリガー
			m_triggerFlag = true;
		}

		// フレーム加算
		pKeyInfo->frame++;
	}

	// ログをとる
	memmove(&m_keyInfoArrayLog[1], &m_keyInfoArrayLog[0], sizeof(KeyInfoArray) * (KEY_INFO_LOG-1));
	memcpy(&m_keyInfoArrayLog[0], m_keyInfoArray, sizeof(KeyInfoArray));
}

void KeyManager::lateProcess(float delta)
{
}

void KeyManager::clear()
{
	memset(&m_keyInfoArray, 0, sizeof(KeyInfoArray));
	for(int i = 0; i < KEY_INFO_MAX; i++)
	{
		m_keyInfoArray[i].status = STATUS_FREE;
	}

	memset(&m_keyInfoArrayLog, 0, sizeof(KeyInfoArray) * KEY_INFO_LOG);
	for(int i = 0; i < KEY_INFO_LOG; i++)
	{
		for(int j = 0; j < KEY_INFO_MAX; j++)
		{
			m_keyInfoArrayLog[i][j].status = STATUS_FREE;
		}
	}
}
