#pragma once

#include "KeyManager.h"
#include "TouchManager.h"

class InputManager {

public:

	static InputManager *getInstance();

private:

	InputManager();
	~InputManager();

public:

	void initialize();
	void finalize();
	void process(float delta);
	void lateProcess(float delta);
	void clear();

	bool getInputFlag() const { return m_inputFlag; }
	void setInputFlag(bool flag) { m_inputFlag = flag; }
	bool getTemporaryInputFlag() const { return m_temporaryInputFlag; }
	void setTemporaryInputFlag(bool flag) { m_temporaryInputFlag = flag; }
	bool isValid() const { return m_inputFlag && m_temporaryInputFlag; }

	KeyManager &getKeyManager() { return m_keyManager; }
	TouchManager &getTouchManager() { return m_touchManager; }

private:

	bool m_inputFlag;
	bool m_temporaryInputFlag;

	KeyManager m_keyManager;
	TouchManager m_touchManager;

};

inline InputManager &GetInputManager()
{
	return *InputManager::getInstance();
}

inline KeyManager &GetKeyManager()
{
	return InputManager::getInstance()->getKeyManager();
}

inline TouchManager &GetTouchManager()
{
	return InputManager::getInstance()->getTouchManager();
}
