#include "Stdafx.h"
#include "Tiger.h"
#include "Player.h"
#include "Vermouth.h"

HRESULT Tiger::init(void)
{
	// 공통
	_tick = 0;
	_step.reset();

	// 스킬시작서클
	_circleFrame = 0;

	// 호랑이
	_ti.x = _ti.y = _ti.frame = 0;
	_ti.alpha = 255;

	// 번개
	_light.pillarFrame = 0;
	_light.groundFrame = 0;
	_light.alpha = 200;
	
	return S_OK;
}

void Tiger::release(void)
{
	// 스킬 사용 순서
	/*
	0==0 스킬구
	0==1 호랑이
	1==1 번개
	
	
	
	*/
}

void Tiger::update(Player* _pl, Vermouth* _ve)
{
	// 공통
	_tick++;
	



	// 시작 서클
	if (_step[0] == 0)
	{
		if (_tick % 7 == 0) _circleFrame++;

		// 상태로 사운드 1번만나올수잇게설정
		if(_pl->getPL()._state !=3)	SOUNDMANAGER->play("스킬구", 1.0f);
		_pl->setPState(3);

		// 끝나고 다음장면
		if (_circleFrame > IMAGEMANAGER->findImage("스킬구")->getMaxFrameX())
		{
			_ti.x = _pl->getPL()._x - 100;
			_ti.y = _pl->getPL()._y - 250;
			_step.set(0, 1);
		}
	}

	// 호랑이
	if (_step[0] == 1)
	{
		if (_tick % 10 == 0) _ti.frame++;
		if (_ti.alpha > 3)_ti.alpha -= 2;
		if (_ti.frame > IMAGEMANAGER->findImage("호랑이")->getMaxFrameX())
			_ti.frame = IMAGEMANAGER->findImage("호랑이")->getMaxFrameX();
		
		_ti.y++;

		// 초기화하고 다음 장면
		if (_ti.alpha <= 3)
		{
			// _step.reset();	리셋하면 시작서클 또 나와서 리셋하면안됨
			_step.set(1, 1);
		}

	}

	if (_step[1] == 1)
	{
		if (_tick % 15 == 0)_light.pillarFrame++;
		if (_light.pillarFrame > IMAGEMANAGER->findImage("번개기둥")->getMaxFrameX())_light.pillarFrame = 0;

		if (_tick % 7 == 0)_light.groundFrame++;
		if (_light.groundFrame > IMAGEMANAGER->findImage("번개바닥")->getMaxFrameX())_light.groundFrame = 0;
	}
	
}

void Tiger::render(Player* _pl, Vermouth* _ve)
{
	if (_step[0] == 0)
	{
		IMAGEMANAGER->findImage("스킬구")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _circleFrame, 0);
	}


	else if (_step[0] == 1)
	{
		IMAGEMANAGER->findImage("호랑이")->alphaFrameRender(getMemDC(), _ti.x, _ti.y, _ti.alpha, _ti.frame, 0);
	}
	

	if (_step[1] == 1)
	{
		// IMAGEMANAGER->findImage("번개바닥")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, _light.alpha, _light.groundFrame, 0);
		// IMAGEMANAGER->findImage("번개기둥")->alphaFrameRender(getMemDC(), _ve->getVE()._x-32, _ve->getVE()._y-290, _light.alpha, _light.pillarFrame, 0);

		IMAGEMANAGER->findImage("토탈번개")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, 40, _light.groundFrame, 0);
		IMAGEMANAGER->findImage("토탈번개광원")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, _light.alpha, _light.groundFrame, 0);
	}

	










}
