#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_dia = new Dialogue;
	_dia->init(1);

	// 버몬트움직임
	_verX = 280;
	_verY = 400;
	_verFrame = 0;

	// 살라딘 움직임
	_salX = 250;
	_salY = 600;
	_saraFrame = 0;

	// 셰라 죽을때 
	_dieFrame = 0;
	// 전체 틱
	_tick = 0;

	// 셰라 프레임
	_saraFrame = 0;

	// 메인 배경 알파
	_BGalpha = 0;

	// 다이얼로그 카운트
	_diaCount = 0;

	// 큰이미지
	_bigImageAlpha2 = _bigImageAlpha = 0;

	// 다이얼로그 사운드 초기화
	_diaSound.reset();

	// 마지막 알파
	_lastAlpha = 255;

	return S_OK;
}

void firstCutScene::release(void)
{
	SAFE_DELETE(_dia);
}

void firstCutScene::update(void)
{
	_tick++;

	// 메인배경 알파
	_BGalpha++;
	if (_BGalpha >= 255) _BGalpha = 255;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stopAllSound();
		_diaCount = 22;
	}

	_dia->update();

}

void firstCutScene::render(void)
{
	// 셰라 죽기 전까지 배경그러주기
	if (!_diaSound[29])
	{
		IMAGEMANAGER->findImage("컷신배경")->alphaRender(getMemDC(), _BGalpha);
		
		if (!_die)
			IMAGEMANAGER->findImage("셰라죽음")->frameRender(getMemDC(), 180, 380, _saraFrame, 0);

		if (_verX > 0)
			IMAGEMANAGER->findImage("살라딘_대기2")->frameRender(getMemDC(), _salX, _salY, 0, 3);
		else if (_dieFrame ==0)
			IMAGEMANAGER->findImage("살라딘_걷기2")->frameRender(getMemDC(), _salX, _salY, _salFrame, 3);


		

		// 배경음악
		if (!_diaSound[30])
		{
			SOUNDMANAGER->play("1번시나리오배경음악", 0.1f);
			_diaSound.set(30, 1);
		}
	}
	if (_diaCount >= 18)
	{
		IMAGEMANAGER->findImage("2번전투시작전배경")->alphaRender(getMemDC(), _lastAlpha);
	}

#pragma region 셰라 죽기 전
// 버몬트 - 기다리고잇엇다
	if (_diaCount == 0)
	{
		if (_BGalpha < 255)_tick = 0;
		if (_BGalpha == 255)
		{
			// 캐릭터 알파 렌더
			if (_tick < 200)
			{
				_bigImageAlpha += 5;
				if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
			}
			else if (SOUNDMANAGER->getLength("기다리고잇엇다") == SOUNDMANAGER->getPosition("기다리고잇엇다"))
			{
				_bigImageAlpha -= 5;
				if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			}
			IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

			//다이얼로그 사운드
			if (!_diaSound[0])
			{
				_diaSound.set(0, 1);
				SOUNDMANAGER->play("기다리고잇엇다", 1.0f);
			}

			// 다이얼로그 창
			IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

			_dia->drawTextNoSkip(_diaCount, 120, 590, 200, 200, 25, 255, 255, 255);

			// 다음 넘기기
			if (_bigImageAlpha == 0)
			{
				_bigImageAlpha = 0;
				_diaCount++;
				_tick = 0;
			}

		}
	}

// 살라딘 - ...
	else if (_diaCount == 1)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 200, 200, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// 버몬트 - 지난번엔 ~~~
	else if (_diaCount == 2)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("지난번엔") == SOUNDMANAGER->getPosition("지난번엔"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[1])
		{
			_diaSound.set(1, 1);
			SOUNDMANAGER->play("지난번엔", 1.0f);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// 셰라 - 살라딘님 ...
	else if (_diaCount == 3)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("셰라-살라딘") == SOUNDMANAGER->getPosition("셰라-살라딘"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("셰라")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[2])
		{
			_diaSound.set(2, 1);
			SOUNDMANAGER->play("셰라-살라딘", 1.0f);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// 살라딘 걱정마시오
	else if (_diaCount == 4)
	{
	// 캐릭터 알파 렌더
	if (_tick < 200)
	{
		_bigImageAlpha += 5;
		if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
	}
	else if (SOUNDMANAGER->getLength("셰라자드걱정마시오") == SOUNDMANAGER->getPosition("셰라자드걱정마시오"))
	{
		_bigImageAlpha -= 5;
		if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
	}

	// 캐릭터 이미지
	IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

	//다이얼로그 사운드
	if (!_diaSound[3])
	{
		_diaSound.set(3, 1);
		SOUNDMANAGER->play("셰라자드걱정마시오", 1.0f);
	}

	// 다이얼로그 창
	IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
	// 다이얼로그 텍스트
	_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

	if (_bigImageAlpha == 0)
	{
		_bigImageAlpha = 0;
		_diaCount++;
		_tick = 0;
	}
	}

// 버몬트 요새두개
	else if (_diaCount == 5)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			if (_tick % 5 == 0)
			{
				if(_saraFrame < 2)	_saraFrame++;
			}
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("요새두개") == SOUNDMANAGER->getPosition("요새두개"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[4])
		{
			_diaSound.set(4, 1);
			SOUNDMANAGER->play("요새두개", 1.0f);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// 셰라 - 저는 개의치
// 살라딘 - 설마 ...
// 버몬트 - 투르제국 뭐시기
// 사라딘 - 왜그런짓
// 8번 사운드 사용
// 9번 대사 끝
	else if (_diaCount ==6)
	{
		// 캐릭터 알파 렌더
		if (!_sara)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (_sara&&!_ver)
		{

			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)
			{
				_bigImageAlpha = 0;
				_ver = true;
			}
		}
		if (_ver)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}

		if (_sal)
		{
			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
		}

		// 캐릭터 이미지
		if(!_ver)IMAGEMANAGER->findImage("셰라")->alphaRender(getMemDC(), 500, 150, _bigImageAlpha);
		if(_sal) IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), -100, 100, _bigImageAlpha2);
		if (_ver) IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 550, 150, _bigImageAlpha);


		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 180, 580, 215);
		if (_sal) IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 50, 380, 215);


		// 다이얼로그 텍스트
		if(!_ver)_dia->drawTextNoSkip(6, 200, 590, 500, 500, 25, 255, 255, 255);
		else if (_ver)_dia->drawTextNoSkip(8, 200, 590, 800, 500, 25, 255, 255, 255);
		if (_sal && !_last) _dia->drawTextNoSkip(7, 70, 390, 500, 500, 25, 255, 255, 255);
		if (_last) _dia->drawTextNoSkip(9, 70, 390, 500, 500, 25, 255, 255, 255);



		

		//다이얼로그 사운드
		if (!_diaSound[5])
		{
			_diaSound.set(5, 1);
			SOUNDMANAGER->play("셰라개의치", 1.0f);
		}
		if (_sal && !_diaSound[6])
		{
			_diaSound.set(6, 1);
			SOUNDMANAGER->play("살라딘설마", 1.0f);
		}		
		if (_ver && !_diaSound[7])
		{
			_diaSound.set(7, 1);
			SOUNDMANAGER->play("버몬트여술탄", 1.0f);
		}
		if (_last && !_diaSound[8])
		{
			_diaSound.set(8, 1);
			SOUNDMANAGER->play("살라딘왜그런짓", 1.0f);
		}

		// 사운드 끝나면 불값 변화
		if (SOUNDMANAGER->getLength("셰라개의치") == SOUNDMANAGER->getPosition("셰라개의치"))
		{
			_sal = true;
		}
		if (SOUNDMANAGER->getLength("살라딘설마") == SOUNDMANAGER->getPosition("살라딘설마"))
		{
			_sara = true;
		}
		if (SOUNDMANAGER->getLength("버몬트여술탄") == SOUNDMANAGER->getPosition("버몬트여술탄"))
		{
			_last = true;
		}		
		if (SOUNDMANAGER->getLength("살라딘왜그런짓") == SOUNDMANAGER->getPosition("살라딘왜그런짓"))
		{
			_diaCount=10;
			_bigImageAlpha = _bigImageAlpha2 = 0;
			_ver = _sara = _sal = false;
			_tick = 0;
		}
	}

// 10번 대사
// 9번 음성
// 버몬트 - 복수다
	else if (_diaCount == 10)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("버몬트복수다") == SOUNDMANAGER->getPosition("버몬트복수다"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[9])
		{
			SOUNDMANAGER->play("버몬트복수다", 1.0f);
			_diaSound.set(9, 1);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// 다음 턴 넘기기
		if(_bigImageAlpha==0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}
	}

// 11번대사
// 10번 음성 사용
// 살라딘 - 칼버리겟다
	else if (_diaCount == 11)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("살라딘칼버림") == SOUNDMANAGER->getPosition("살라딘칼버림"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}
		// 캐릭터 이미지
		IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[10])
		{
			SOUNDMANAGER->play("살라딘칼버림", 1.0f);
			_diaSound.set(10, 1);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// 다음 턴 넘기기
		if (_bigImageAlpha==0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}

	}

// 13번까지 대사
// 12번까지 음성 사용
// 셰라 -안되요
	else if (_diaCount == 12)
	{
	_saraFrame = 3;
	// 캐릭터 알파 렌더
		if (!_sara)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (_sal && !_sara)
		{
			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
		}
		else if (_sara)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <=0)_bigImageAlpha2 = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("셰라")->alphaRender(getMemDC(), 500, 150, _bigImageAlpha);
		if (_sal) IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), -100, 100, _bigImageAlpha2);


		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 180, 580, 215);
		if (_sal) IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 50, 380, 215);


		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 200, 590, 500, 500, 25, 255, 255, 255);
		if (_sal) _dia->drawTextNoSkip(13, 70, 390, 800, 500, 25, 255, 255, 255);





		//다이얼로그 사운드
		if (!_diaSound[11])
		{
			_diaSound.set(11, 1);
			SOUNDMANAGER->play("셰라안되요", 1.0f);
		}
		if (_sal&&!_diaSound[12])
		{
			_diaSound.set(12, 1);
			SOUNDMANAGER->play("살라딘투르인", 1.0f);
		}
		// 사운드 끝나면 불값 변화
		if (SOUNDMANAGER->getLength("셰라안되요") == SOUNDMANAGER->getPosition("셰라안되요"))
		{
			_sal = true;
		}
		
		if (SOUNDMANAGER->getLength("살라딘투르인") == SOUNDMANAGER->getPosition("살라딘투르인"))
		{
			_sara = true;
		}

		if (_bigImageAlpha == 0)
		{
			_diaCount=14;
			_bigImageAlpha = _bigImageAlpha2 = 0;
			_ver = _sara = _sal = false;
			_tick = 0;
		}
		
	}

// 14번까지 대사
// 13번까지 음성
// 버몬트 - 체포해라
	else if (_diaCount == 14)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("버몬트체포해라") == SOUNDMANAGER->getPosition("버몬트체포해라"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		
		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[13])
		{
			SOUNDMANAGER->play("버몬트체포해라", 1.0f);
			_diaSound.set(13, 1);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// 다음 턴 넘기기
		if (_bigImageAlpha == 0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}
	}

// 15번까지 대사
// 15번까지 음성
// 셰라자살
// 살라딘 - 안돼
	else if (_diaCount == 15)
	{

		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (_bigImageAlpha2 == 255)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		if (_bigImageAlpha == 0)
		{
			if (_tick % 5 == 0)
			{
				if(_saraFrame < 14)_saraFrame++;
				if (_saraFrame == 13)
				{
					_bigImageAlpha2 = 0;
				}
			}

			if (_saraFrame == 14)
			{
				IMAGEMANAGER->findImage("빨강알파")->alphaRender(getMemDC(), _bigImageAlpha2);
				_bigImageAlpha2+=5;
				if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
			}		
		}
		
		if (SOUNDMANAGER->getLength("셰라자살") == SOUNDMANAGER->getPosition("셰라자살"))
		{
			// 15번 다이얼로그에서만 사용하기위해 임시 사용
			_bigImageAlpha2 = 255;
		}

		if (!_diaSound[15] && _bigImageAlpha ==0)
		{
			_diaSound.set(15, 1);
			SOUNDMANAGER->play("살라딘안돼", 1.0f);
		}

		// 캐릭터 이미지
		if (_bigImageAlpha != 0)
		IMAGEMANAGER->findImage("셰라")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[14])
		{
			_diaSound.set(14, 1);
			SOUNDMANAGER->play("셰라자살", 1.0f);
		}

		// 다이얼로그 창
		if (_bigImageAlpha != 0)
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		if (_bigImageAlpha != 0)
		_dia->drawTextNoSkip(_diaCount, 120, 590, 800, 500, 25, 255, 255, 255);

		// 턴넘기기
		if (SOUNDMANAGER->getLength("살라딘안돼") == SOUNDMANAGER->getPosition("살라딘안돼"))
		{
			_bigImageAlpha = 0;
			_bigImageAlpha2 = 255;
			_diaCount++;
			_tick = 0;
		}
	}

// 16번 대사,음성 사용
// 버몬트 - 제길
	else if (_diaCount == 16)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <= 0)_bigImageAlpha2 = 0;
		}
		IMAGEMANAGER->findImage("빨강알파")->alphaRender(getMemDC(), _bigImageAlpha2);


		// 빨간화면 사라지면 대사 시작
		if (_bigImageAlpha2 == 0)
		{
			if (_tick % 5 == 0)
			{
				_saraFrame++;
				if (_saraFrame > IMAGEMANAGER->findImage("셰라죽음")->getMaxFrameX())
					_saraFrame = IMAGEMANAGER->findImage("셰라죽음")->getMaxFrameX();
			}

			if (_saraFrame == IMAGEMANAGER->findImage("셰라죽음")->getMaxFrameX())
			{
				if (!_sal)
				{
					_bigImageAlpha += 5;
					if (_bigImageAlpha >= 255)
					{
						_bigImageAlpha = 255;
					}
				}
				else if (_sal)
				{
					_bigImageAlpha -= 5;
					if (_bigImageAlpha <=0)
					{
						_bigImageAlpha = 0;
					}
				}
				

				if (SOUNDMANAGER->getLength("버몬트제길") == SOUNDMANAGER->getPosition("버몬트제길"))
				{
					_sal = true;
				}

				// 캐릭터 이미지
				IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

				//다이얼로그 사운드
				if (!_diaSound[16])
				{
					SOUNDMANAGER->play("버몬트제길", 1.0f);
					_diaSound.set(16, 1);
				}

				// 다이얼로그 창
				if(_bigImageAlpha != 0)
				IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

				// 다이얼로그 텍스트
				if (_bigImageAlpha != 0)
				_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

				if (_bigImageAlpha == 0)
				{
					_die = true;
					if (_tick % 5 == 0)
					{
						_verFrame++;
						if (_verFrame > IMAGEMANAGER->findImage("버몬트_걷기")->getMaxFrameX())
							_verFrame =0;
					}

					
					IMAGEMANAGER->findImage("셰라죽을때")->frameRender(getMemDC(), 213, 432, _dieFrame, 0);
					IMAGEMANAGER->findImage("버몬트_걷기2")->frameRender(getMemDC(), _verX, _verY, _verFrame, 0);
					
					if (_verY < 500)
					{
						_verY += 5;
						_verX -= 5;
					}
					else
					{
						_verX -= 5;
					}
					if (_verX < 0 && _salY > 465)
					{
						if (_tick % 3 == 0)_salFrame++;
						if (_salFrame > 6)_salFrame = 0;
						_salY -= 5;
					}
					else if (_verX < 0 && _salY <= 465)
					{
						if (_tick % 15 == 0)_dieFrame++;
					}
				}

				// 다음 턴 넘기기
				if (_dieFrame >= 3)
				{
					_diaCount++;
					_tick = 0;
					_bigImageAlpha = 0;
					_BGalpha = 0;
					IMAGEMANAGER->findImage("검정알파")->render(getMemDC());
				}
			}
		}
	}
#pragma endregion

#pragma region 셰라 죽은후
// 17번 음성 사용
// 음성 30번까지 사용
// 살라딘 - 이게 무슨짓
	else if (_diaCount == 17)
	{
		// 배경음악
		if (!_diaSound[22])
		{
			SOUNDMANAGER->stopAllSound();
			_diaSound.set(22, 1);
			SOUNDMANAGER->play("배경셰라언젠가말할때", 0.2f);
		}
		// 배경이미지 알파
		// 셰라 눈뜸
		if (!_diaSound[29])
		{
			_BGalpha += 5;
			if (_BGalpha >= 255)_BGalpha = 255;
		}		
		// 셰라 눈감음
		if (SOUNDMANAGER->getLength("셰라안녕")== SOUNDMANAGER->getPosition("셰라안녕"))
		{
			_BGalpha -= 5;
			if (_BGalpha <=0)_BGalpha = 0;

			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;

		}


		//IMAGEMANAGER->findImage("검정알파")->render(getMemDC());
		//IMAGEMANAGER->findImage("셰라죽음배경")->alphaRender(getMemDC(), _BGalpha);
		//
		//// 살라딘 이게 무슨짓
		//if (_BGalpha == 255)
		//{


		//	if (!_diaSound[17])
		//	{
		//		_diaSound.set(17, 1);
		//		SOUNDMANAGER->play("살라딘이게무슨짓", 1.0f);
		//	}
		//}

		//// 셰라 순결잃음 재생
		//if (SOUNDMANAGER->getLength("살라딘이게무슨짓") == SOUNDMANAGER->getPosition("살라딘이게무슨짓"))
		//{
		//	if (!_diaSound[18])
		//	{
		//		_diaSound.set(18, 1);
		//		SOUNDMANAGER->play("셰라순결",1.0f);
		//	}
		//}

		//// 셰라 투르선택 감사
		//if (SOUNDMANAGER->getLength("셰라순결") == SOUNDMANAGER->getPosition("셰라순결"))
		//{
		//	if (!_diaSound[19])
		//	{
		//		_diaSound.set(19, 1);
		//		SOUNDMANAGER->play("셰라투르선택감사", 1.0f);
		//	}
		//}

		//// 살라딘 이젠늦엇소
		//if (SOUNDMANAGER->getLength("셰라투르선택감사") == SOUNDMANAGER->getPosition("셰라투르선택감사"))
		//{
		//	if (!_diaSound[20])
		//	{
		//		_diaSound.set(20, 1);
		//		SOUNDMANAGER->play("살라딘이젠늦엇소", 1.0f);
		//	}
		//}
		
		// 셰라 언젠가말씀
		if (SOUNDMANAGER->getLength("살라딘이젠늦엇소") == SOUNDMANAGER->getPosition("살라딘이젠늦엇소"))
		{

		}

		if (!_diaSound[21])
		{
			_diaSound.set(21, 1);
			SOUNDMANAGER->play("셰라언젠가말씀", 1.0f);
		}
		// 살라딘 죽으면안되오
		if (SOUNDMANAGER->getLength("셰라언젠가말씀") == SOUNDMANAGER->getPosition("셰라언젠가말씀"))
		{
			if (!_diaSound[35])
			{
				_diaSound.set(35, 1);
				SOUNDMANAGER->play("살라딘죽으면안되오", 1.0f);
			}
		}

		// 셰라 약속해줘
		if (SOUNDMANAGER->getLength("살라딘죽으면안되오") == SOUNDMANAGER->getPosition("살라딘죽으면안되오"))
		{
			if (!_diaSound[23])
			{
				_diaSound.set(23, 1);
				SOUNDMANAGER->play("셰라약속해줘", 1.0f);
			}
		}

		// 살라딘 하지만녀석들
		if (SOUNDMANAGER->getLength("셰라약속해줘") == SOUNDMANAGER->getPosition("셰라약속해줘"))
		{
			if (!_diaSound[24])
			{
				_diaSound.set(24, 1);
				SOUNDMANAGER->play("살라딘하지만녀석들", 1.0f);
			}
		}

		// 셰라 마지막소원
		if (SOUNDMANAGER->getLength("살라딘하지만녀석들") == SOUNDMANAGER->getPosition("살라딘하지만녀석들"))
		{
			if (!_diaSound[25])
			{
				_diaSound.set(25, 1);
				SOUNDMANAGER->play("셰라마지막소원", 1.0f);
			}
		}

		// 살라딘 어려운약속
		if (SOUNDMANAGER->getLength("셰라마지막소원") == SOUNDMANAGER->getPosition("셰라마지막소원"))
		{
			if (!_diaSound[26])
			{
				_diaSound.set(26, 1);
				SOUNDMANAGER->play("살라딘어려운약속", 1.0f);
			}
		}

		// 셰라 그런느낌
		if (SOUNDMANAGER->getLength("살라딘어려운약속") == SOUNDMANAGER->getPosition("살라딘어려운약속"))
		{
			if (!_diaSound[27])
			{
				_diaSound.set(27, 1);
				SOUNDMANAGER->play("셰라그런느낌", 1.0f);
			}

		}

		// 살라딘 셰라자드
		if (SOUNDMANAGER->getLength("셰라그런느낌") == SOUNDMANAGER->getPosition("셰라그런느낌"))
		{
			if (!_diaSound[28])
			{
				_diaSound.set(28, 1);
				SOUNDMANAGER->play("살라딘셰라자드", 1.0f);
			}
		}

		// 셰라 안녕
		if (SOUNDMANAGER->getLength("살라딘셰라자드") == SOUNDMANAGER->getPosition("살라딘셰라자드"))
		{
			IMAGEMANAGER->findImage("셰라눈감음")->render(getMemDC());

			if (!_diaSound[29])
			{
				_diaSound.set(29, 1);
				SOUNDMANAGER->play("셰라안녕", 1.0f);
			}
		}


		IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);

		// 끝
		if (_bigImageAlpha==255)
		{
			_diaCount++;
			_BGalpha = 0;
			_tick = 0;
			_bigImageAlpha = 255;
		}

	}

#pragma endregion

#pragma region 2번 전투전 마지막 시나리오

// 대사 17번
// 사운드 31번
// 2번 전투 시작전 마지막씬
// 버몬트 - 다끝내셧나?
	else if (_diaCount == 18)
	{
		if (!_diaSound[34])
		{
			SOUNDMANAGER->stopAllSound();
			_diaSound.set(34, 1);
			SOUNDMANAGER->play("dia18번배경", 0.2f);
		}
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >=255)_bigImageAlpha2 = 255;
		}

		if (SOUNDMANAGER->getLength("버몬트다끝나셧나") == SOUNDMANAGER->getPosition("버몬트다끝나셧나"))
		{
			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <= 0)_bigImageAlpha2 = 0;
		}

		IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha2);

		//다이얼로그 사운드
		if (!_diaSound[31])
		{
			_diaSound.set(31, 1);
			SOUNDMANAGER->play("버몬트다끝나셧나", 1.0f);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(17, 120, 590, 1000, 500, 25, 255, 255, 255);

		
		if (_bigImageAlpha2 == 0)
		{
			_bigImageAlpha2 = 0;
			_bigImageAlpha = 0;
			_tick = 0;
			_diaCount++;
		}
	}

// 살라딘 - 불쌍한인간
	else if (_diaCount == 19)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("살라딘복수심에") == SOUNDMANAGER->getPosition("살라딘복수심에"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[32])
		{
			SOUNDMANAGER->play("살라딘복수심에", 1.0f);
			_diaSound.set(32, 1);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(18, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

	else if (_diaCount == 20)
	{
		// 캐릭터 알파 렌더
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("버몬트각오해라") == SOUNDMANAGER->getPosition("버몬트각오해라"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// 캐릭터 이미지
		IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//다이얼로그 사운드
		if (!_diaSound[33])
		{
			SOUNDMANAGER->play("버몬트각오해라", 1.0f);
			_diaSound.set(33, 1);
		}

		// 다이얼로그 창
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);
		// 다이얼로그 텍스트
		_dia->drawTextNoSkip(19, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}
	else if (_diaCount == 21)
	{
		_lastAlpha -= 5;
		if (_lastAlpha <= 0)
		{
			_lastAlpha = 0;
			SCENEMANAGER->changScene("로딩","전투");
		}
	}
	else if (_diaCount==22)
	{
	IMAGEMANAGER->findImage("검정알파")->render(getMemDC());
	SCENEMANAGER->changScene("로딩", "전투");
	}

#pragma endregion

}

