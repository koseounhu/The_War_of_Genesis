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
	_light.frame = 0;
	_light.alpha = 150;

	// 시작시 0번 1로 설정 해놔야 스킬 사용가능 , 스킬끝나면 비트셋 리셋하고 0번을 다시 1로 만들것
	_step.set(0, 1);
	
	return S_OK;
}

void Tiger::release(void)
{
	// 스킬 사용 순서
	/*
	0==1 스킬구
	1==1 호랑이
	2==1 번개
	3==1 
	
	
	*/
}

void Tiger::update(Player* _pl, Vermouth* _ve)
{
	// 공통
	_tick++;
	
	// 시작 서클
	if (_step[0])
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
			_step.reset();
			_step.set(1, 1);
		}
	}

	// 호랑이
	if (_step[1])
	{
		if (!SOUNDMANAGER->isPlaySound("호랑이")) SOUNDMANAGER->play("호랑이", 1.0f);

		if (_tick % 10 == 0) _ti.frame++;
		if (_ti.alpha > 3)_ti.alpha -= 2;
		if (_ti.frame > IMAGEMANAGER->findImage("호랑이")->getMaxFrameX())
			_ti.frame = IMAGEMANAGER->findImage("호랑이")->getMaxFrameX();
		
		_ti.y++;

		// 초기화하고 다음 장면
		if (_ti.alpha <= 3)
		{
			_step.reset();
			_step.set(2, 1);	// 번개
			_step.set(3, 1);	// 돌진

			// 돌진기 세팅
			for (int i = 0; i < _countof(_dash); i++)
			{
				_dash[i].x = _pl->getPL()._x - 70;
				_dash[i].y = _pl->getPL()._y - 80;
				_dash[i].speed = 15.0f;
				_dash[i].frame = 0;
				_dash[i].effectFrame = 0;
				_dash[i].alpha = 255;
			}
		}
	}

	// 번개
	if (_step[2])
	{
		if (_tick % 5 == 0)_light.frame++;
		if (_light.frame > IMAGEMANAGER->findImage("토탈번개")->getMaxFrameX())
		{
			_light.frame = 0;
			_step.set(2, 0);
		}
	}

	// 돌진
	if (_step[3])
	{
		if (!_atkSound)
		{
			SOUNDMANAGER->play("호랑이어택", 1.0f);
			_atkSound = true;
		}

#pragma region 돌진 좌측
		// 쉐도우 세팅
		for (int i = 0; i < 8; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].x = _dash[0].x;
				_shadow[i].y = _dash[0].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// 사이드 세팅
		for (int i = 8; i < 10; i++)
		{
			if (!_shadow[7].start)
			{
				_shadow[i].x = _shadow[0].x;
				_shadow[i].y = _shadow[0].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}

		// 살라딘 
		if (_pl->getPL()._x - 270 < _dash[0].x)
		{
			_dash[0].x -= _dash[0].speed;
			if (_dash[0].speed >= 0) _dash[0].speed -= 0.5;
		}
		// 살라딘 위아래
		if (_dash[0].x < _shadow[8].x)
		{
			_shadow[8].x -= _shadow[8].speed;
			if (_shadow[8].speed >= 0) _shadow[8].speed -= 0.5;
			_shadow[9].x -= _shadow[9].speed;
			if (_shadow[8].speed >= 0) _shadow[9].speed -= 0.5;
		}
		if(_dash[0].x == _shadow[8].x) _dash[0].frame++;

		if (_dash[0].effectFrame >=4)
		{
			_dash[0].frame++;
		}
		
		// 이펙트
		if (_tick % 12 == 0 && _pl->getPL()._x - 90 > _dash[0].x)_dash[0].effectFrame++;
#pragma endregion

#pragma region 돌진 우측

		// 쉐도우 세팅
		for (int i = 10; i < 18; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].x = _dash[1].x+50;
				_shadow[i].y = _dash[1].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// 사이드 세팅
		for (int i = 18; i < 20; i++)
		{
			if (!_shadow[17].start)
			{
				_shadow[i].x = _shadow[10].x;
				_shadow[i].y = _shadow[10].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// 살라딘 
		if (_pl->getPL()._x + 230 > _dash[1].x)
		{
			_dash[1].x += _dash[1].speed;
			if (_dash[1].speed >5) _dash[1].speed -= 0.5;
		}
		// 살라딘 좌우
		if (_dash[1].x > _shadow[18].x)
		{
			
			_shadow[18].x += _shadow[18].speed;
			if (_shadow[18].speed >5) _shadow[18].speed -= 0.5;
			_shadow[19].x += _shadow[19].speed;
			if (_shadow[18].speed >5) _shadow[19].speed -= 0.5;
		}
		if (_dash[1].x == _shadow[18].x) _dash[1].frame++;

		if (_dash[1].effectFrame >= 4)
		{
			_dash[1].frame++;
		}

		// 이펙트
		if (_tick % 12 == 0 && _pl->getPL()._x < _dash[1].x)_dash[1].effectFrame++;

#pragma endregion

		// 돌진기 끝
		if (SOUNDMANAGER->getPosition("호랑이") >=2500 )
		{
			_atkSound = false;

			_step.set(3, 0);
			_step.set(4, 1);
			for (int i = 0; i < _countof(_dash); i++)
			{
				_dash[i].x = _pl->getPL()._x - 70;
				_dash[i].y = _pl->getPL()._y - 80;
				_dash[i].speed = 15.0f;
				_dash[i].frame = 0;
				_dash[i].effectFrame = 0;
				_dash[i].alpha = 255;
			}
		}
	}
	
}

void Tiger::render(Player* _pl, Vermouth* _ve)
{
	// 스킬시작
	if (_step[0])
	{
		IMAGEMANAGER->findImage("스킬구")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _circleFrame, 0);
	}

	// 호랑이
	else if (_step[1])
	{
		IMAGEMANAGER->findImage("호랑이")->alphaFrameRender(getMemDC(), _ti.x, _ti.y, _ti.alpha, _ti.frame, 0);
	}


	// 돌진
	if (_step[3])
	{
		_pl->setPState(5); // 플레이어 가리기

		// 쉐도우 렌더
		for (int i = 0; i < 10; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 10; i < 20; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 20; i < 30; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 30; i < 40; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}

		// 좌측
		for (int i = 0; i < 8; i++)
		{
			IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[i].x, _shadow[i].y, _shadow[i].alpha, 0, 0);
		}
		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[8].x, _shadow[8].y - 60, _shadow[8].alpha, 0, 0);
		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[9].x, _shadow[9].y + 60, _shadow[9].alpha, 0, 0);

		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _dash[0].x, _dash[0].y, _dash[0].alpha, _dash[0].frame, 0);
		IMAGEMANAGER->findImage("돌진이펙트")->alphaFrameRender(getMemDC(), _dash[0].x - 70, _dash[0].y - 50, _dash[0].alpha, _dash[0].effectFrame, 0);

		// 우측
		for (int i = 10; i < 18; i++)
		{
			IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[i].x, _shadow[i].y, _shadow[i].alpha, 0, 1);
		}
		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[18].x, _shadow[18].y - 60, _shadow[18].alpha, 0, 1);
		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _shadow[19].x, _shadow[19].y + 60, _shadow[19].alpha, 0, 1);

		IMAGEMANAGER->findImage("살라딘돌진기")->alphaFrameRender(getMemDC(), _dash[1].x, _dash[1].y, _dash[1].alpha, _dash[1].frame, 1);
		IMAGEMANAGER->findImage("돌진이펙트")->alphaFrameRender(getMemDC(), _dash[1].x, _dash[1].y - 50, _dash[1].alpha, _dash[1].effectFrame, 1);
	}
	
	// 업데이트되는 순서와 렌더링 순서 일부로 다르게함
	// 번개
	if (_step[2])
	{
		IMAGEMANAGER->findImage("토탈번개")->alphaFrameRender(getMemDC(), _ve->getVE()._x - 85, _ve->getVE()._y - 315, 40, _light.frame, 0);
		IMAGEMANAGER->findImage("토탈번개광원")->alphaFrameRender(getMemDC(), _ve->getVE()._x - 85, _ve->getVE()._y - 365, _light.alpha, _light.frame, 0);
	}



	if (_step[4])
	{
		_pl->setPState(0); // 플레이어 그리기
	}

	











}
