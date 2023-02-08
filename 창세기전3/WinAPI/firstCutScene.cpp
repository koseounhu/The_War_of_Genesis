#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_dia = new Dialogue;
	_dia->init(1);

	// 전체 틱
	_tick = 0;

	// 메인 배경 알파
	_BGalpha = 0;

	// 다이얼로그 카운트
	_diaCount = 15;

	// 큰이미지
	_bigImageAlpha2 = _bigImageAlpha = 0;

	// 다이얼로그 사운드 초기화
	_diaSound.reset();

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


	_dia->update();
}


void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("컷신배경")->alphaRender(getMemDC(), _BGalpha);

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
		else if (SOUNDMANAGER->getLength("셰라자살") == SOUNDMANAGER->getPosition("셰라자살"))
		{
			_bigImageAlpha -= 10;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			
			if (!_diaSound[15])
			{
				_diaSound.set(15, 1);
				SOUNDMANAGER->play("살라딘안돼", 1.0f);
			}
		}

		// 캐릭터 이미지
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
		_dia->drawTextNoSkip(_diaCount, 120, 590, 800, 500, 25, 255, 255, 255);


		// 임시
		if (SOUNDMANAGER->getLength("셰라자살") == SOUNDMANAGER->getPosition("셰라자살"))
		{
			_bigImageAlpha = 0;
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
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("버몬트제길") == SOUNDMANAGER->getPosition("버몬트제길"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
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





}

