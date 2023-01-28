#include "Stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}


HRESULT KeyManager::init(void)
{
	//키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}

	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	/*
	GetAsyncKeyState
	- 어떤 키가 입력된건지 체크 or 프로그램에서 키를 입력받고 싶을때 사용하는 API 공용 함수
	- 메세지 큐에 있는 키의 정보를 확인한다(가져온다).
	- 키가 눌린 시점을 체크하기 위해 &(And) 연산을 사용
	*/

	//AND 연산: & 연산자
	//ㄴ 비트 단위로 AND 연산을 수행한다.
	//ㄴ 둘 다 1일 때만 결과가 1이고, 아니라면 0이다.
	if (GetAsyncKeyState(key) & 0x80000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x80000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
