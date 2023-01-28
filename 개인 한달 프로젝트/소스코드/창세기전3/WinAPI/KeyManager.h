#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	//C언어 스타일(불리언)
	//C언어의 BOOL,TRUE,FALSE와 C++의 bool,true,false을 치환시켜야 한다.
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);

	//키가 한 번만 눌렸는지
	bool isOnceKeyDown(int key);
	//한 번 누르고 띄었는지
	bool isOnceKeyUp(int key);
	//키가 계속 눌려 있는지
	bool isStayKeyDown(int key);
	//토글키
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();
};

