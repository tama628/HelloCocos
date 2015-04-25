#include "InputManager.h"

USING_NS_CC;

static InputManager *g_pInstance;

InputManager *InputManager::getInstance()
{
	if( !g_pInstance )
	{
		g_pInstance = new InputManager();
	}
	return g_pInstance;
}

InputManager::InputManager() :
m_inputFlag(false),
m_temporaryInputFlag(false)
{
}

InputManager::~InputManager()
{
}

void InputManager::initialize()
{
	// フラグの設定
	m_inputFlag = true;
	m_temporaryInputFlag = true;

	// マネージャー
	m_keyManager.initialize();
	m_touchManager.initialize();
}

void InputManager::finalize()
{
	// マネージャー
	m_keyManager.finalize();
	m_touchManager.finalize();

	// インスタンスの削除
	CC_SAFE_DELETE( g_pInstance );
}

void InputManager::process(float delta)
{
	// フラグの設定
	m_temporaryInputFlag = true;

	// マネージャー
	m_keyManager.process( delta );
	m_touchManager.process( delta );
}

void InputManager::lateProcess(float delta)
{
	// マネージャー
	m_keyManager.lateProcess( delta );
	m_touchManager.lateProcess( delta );
}

void InputManager::clear()
{
	// マネージャー
	m_keyManager.clear();
	m_touchManager.clear();
}
