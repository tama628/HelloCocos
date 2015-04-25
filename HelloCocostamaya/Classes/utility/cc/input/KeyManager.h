#pragma once
#include "cocos2d.h"

// キーコード
typedef cocos2d::EventKeyboard::KeyCode KeyCode;

class KeyManager {

	explicit KeyManager( const KeyManager& );

public:

	enum {
		REPEAT_START = 24,
		REPEAT_SPAN = 8,
		REPEATFAST_SPAN = 2,
		KEY_INFO_MAX = 256,
		KEY_INFO_LOG = 300 // 5*60
	};

	enum {
		STATUS_PUSH				= 1 << 0,
		STATUS_PRESS			= 1 << 1,
		STATUS_PRESS_REPEAT		= 1 << 2,
		STATUS_PRESS_REPEATFAST	= 1 << 3,
		STATUS_PULL				= 1 << 4,
		STATUS_FREE				= 1 << 5,
		STATUS_FREE_REPEAT		= 1 << 6,
		STATUS_FREE_REPEATFAST	= 1 << 7
	};

	struct KeyInfo {
		int status;
		int frame;
		int repeatCount;
		int repeatFastCount;
	};

public:

	KeyManager();
	~KeyManager();

	void initialize();
	void finalize();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void process(float delta);
	void lateProcess(float delta);
	void clear();

	// キーの状態を取得
	bool isPush(KeyCode keyCode) const				{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_PUSH) != 0; }
	bool isPress(KeyCode keyCode) const				{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_PRESS) != 0; }
	bool isPressRepeat(KeyCode keyCode) const		{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_PRESS_REPEAT) != 0; }
	bool isPressRepeatFast(KeyCode keyCode) const	{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_PRESS_REPEATFAST) != 0; }
	bool isPull(KeyCode keyCode) const				{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_PULL) != 0; }
	bool isFree(KeyCode keyCode) const				{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_FREE) != 0; }
	bool isFreeRepeat(KeyCode keyCode) const		{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_FREE_REPEAT) != 0; }
	bool isFreeRepeatFast(KeyCode keyCode) const	{ return (m_keyInfoArray[ static_cast<int>(keyCode) ].status & STATUS_FREE_REPEATFAST) != 0; }

	const KeyInfo *getKeyInfo(KeyCode keyCode) const { return &m_keyInfoArray[ static_cast<int>(keyCode) ]; }
	const KeyInfo *getKeyInfoLog(int index, KeyCode keyCode) const { return &m_keyInfoArrayLog[ index ][ static_cast<int>(keyCode) ]; }

	// onKeyPressed()かonKeyReleased()が呼ばれたか
	bool isTrigger() const { return m_triggerFlag; }

private:

	typedef KeyInfo KeyInfoArray[KEY_INFO_MAX];
	KeyInfoArray m_keyInfoArray;
	KeyInfoArray m_keyInfoArrayLog[KEY_INFO_LOG];

	cocos2d::EventListener *m_pEventListener;
	bool m_triggerFlag;

};
