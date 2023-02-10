#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	_tick = _alpha = _count = 0;
	_dia = new Dialogue;
	_dia->init(2);


	_neckX = 660;
	_neckY = 610;
	_neckFrame = 0;

	_effect = 0;
	x = 470;
	y = 610;
	_frame = 0;
	// 다이얼로그 관련 비트셋
	_diaText.reset();
	_diaSound.reset();


	_count = 0;

	// 큰이미지
	_bigImageAlpha = 0;

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_dia);
}

void SecondScene::update(void)
{
	_tick++;

	// 알파값 관리
	if(_count <1)_alpha++;
	if (_alpha >= 255)
	{
		_alpha = 255;
	}

	// 엔딩 프레임
	if (_tick % 25 == 0&& _count ==11 && _alpha ==255)
	{
		_frame++;
		if (_frame > 5)_frame = 5;
	}

	_dia->update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stopAllSound();
		_count = 17;
	}
}

void SecondScene::render(void)
{

	switch (_count)
	{
	case 0:
		IMAGEMANAGER->findImage("2_1")->alphaRender(getMemDC(), _alpha);
		// 사운드 출력
		if (!_diaSound[0]) SOUNDMANAGER->play("버몬트_죽여라", 1.0f);

		// 사운드 추가 출력 안되게 막는 비트셋
		_diaSound.set(0, 1);

		if (_diaText.any() == 0)
		{
			IMAGEMANAGER->findImage("버몬트칼찔림")->render(getMemDC(), x + 150, y);
			IMAGEMANAGER->findImage("살라딘칼")->render(getMemDC(), x, y);
		}


		if (_alpha == 255)
		{

			// 0번 다이얼로그
			if (!_diaText[0])
			{
				// 큰 캐릭터 이미지 출력
				if (SOUNDMANAGER->getLength("버몬트_죽여라") != SOUNDMANAGER->getPosition("버몬트_죽여라"))_bigImageAlpha += 5;
				if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
				IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

				// 다이얼로그 창
				IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

				// 버몬트 - 죽여라
				_dia->drawTextNoSkip(0, 120, 590, 200, 200, 25, 255, 255, 255);

				if (SOUNDMANAGER->getLength("버몬트_죽여라") == SOUNDMANAGER->getPosition("버몬트_죽여라") && _diaText[0] == 0)
				{
					_bigImageAlpha -= 5;
					if (_bigImageAlpha < 0)
					{
						_diaText.set(0, 1);
						_diaText.set(1, 1);
						_bigImageAlpha = 0;
						_tick = 0;
					}
				}

			}


			// 1번 다이얼로그
			if (_diaText[1])
			{
				if (_tick < 250)
				{
					// 큰이미지
					if (_tick < 150)_bigImageAlpha += 5;
					else if (_tick > 150)_bigImageAlpha -= 5;

					if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
					else if (_bigImageAlpha <= 0)_bigImageAlpha = 0;


					IMAGEMANAGER->findImage("살라딘")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);


					// 다이얼로그 창
					IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

					// 살라딘 - ...
					_dia->drawTextNoSkip(1, 120, 590, 200, 200, 25, 255, 255, 255);
				}


				else if (_bigImageAlpha >= 0)
				{
					_diaText.set(1, 0);
					_diaText.set(2, 1);
					_tick = 0;
				}
			}

			// 목걸이 뺏는 장면
			else if (_diaText[2])
			{
				if (_tick % 3 == 0)_neckFrame++;
				if (_neckFrame >= IMAGEMANAGER->findImage("목걸이")->getMaxFrameX()) _neckFrame = 0;

				if (_tick > 100 && _tick < 200)
				{
					if (_tick % 5 == 0)_effect++;
					IMAGEMANAGER->findImage("목걸이뺏기이펙트")->alphaFrameRender(getMemDC(), x + 65, y-15, 100, _effect, 0);
					IMAGEMANAGER->findImage("목걸이뺏김")->render(getMemDC(), x + 170, y);
					IMAGEMANAGER->findImage("살라딘_목걸이")->render(getMemDC(), x + 70, y - 20);

					
					IMAGEMANAGER->findImage("목걸이")->frameRender(getMemDC(), _neckX, _neckY, _neckFrame, 0);
					if (_effect > 1 && _effect<5)
					{
						_neckX--;
						_neckY--;
					}
					else if (_effect > 5 && _effect < 9)
					{
						_neckX-=2;
						_neckY++;
					}
				}
				else if (_tick < 100)
				{
					IMAGEMANAGER->findImage("목걸이뺏김")->render(getMemDC(), x + 170, y);
					IMAGEMANAGER->findImage("살라딘칼")->render(getMemDC(), x, y);
				}

				if (_tick > 200 && _tick < 400)
				{
					IMAGEMANAGER->findImage("목걸이뺏김")->render(getMemDC(), x + 170, y);
					IMAGEMANAGER->findImage("살라딘_휘파람")->frameRender(getMemDC(), x + 70, y - 10, 0, 0);
				}
				else if (_tick > 400)
				{
					_diaText.set(2, 0);
					_diaText.set(3, 1);
					_tick = 0;
					_bigImageAlpha = 0;
				}
			}


			// 2번 다이얼로그
			if (_diaText[3])
			{
				if (SOUNDMANAGER->getLength("버몬트_그것만은") != SOUNDMANAGER->getPosition("버몬트_그것만은"))
				{
					_bigImageAlpha += 5;
					if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
					IMAGEMANAGER->findImage("버몬트")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

					// 다이얼로그 창
					IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), 100, 580, 215);

					// 버몬트 - 그것만은 ..
					_dia->drawTextNoSkip(2, 120, 590, 500, 200, 25, 255, 255, 255);

					// 사운드 추가 출력 안되게 막는 비트셋
					if (!_diaSound[1]) SOUNDMANAGER->play("버몬트_그것만은", 1.0f);
					_diaSound.set(1, 1);
				}
				else if (SOUNDMANAGER->getLength("버몬트_그것만은") == SOUNDMANAGER->getPosition("버몬트_그것만은"))
				{
					_diaText.set(3, 0);
					_diaText.set(4, 1);
					_bigImageAlpha = 0;
					_tick = 0;
				}

			}

			else if (_diaText[4])
			{
				if (!_diaSound[2])
				{
					_diaSound.set(2, 1);
					SOUNDMANAGER->play("휘파람", 0.2f);
				}

				_bigImageAlpha += 2;
				IMAGEMANAGER->findImage("목걸이뺏김")->render(getMemDC(), x + 170, y);
				IMAGEMANAGER->findImage("살라딘_휘파람")->frameRender(getMemDC(), x + 70, y - 10, 1, 0);
				IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);

				if (_bigImageAlpha >= 255)
				{
					_alpha = 0;
					_bigImageAlpha = 255;
					_count++;
				}
			}


		}

		break;

	case 1:
		IMAGEMANAGER->findImage("2_2")->alphaRender(getMemDC(), _alpha);

		break;

	case 2:
		IMAGEMANAGER->findImage("2_3")->alphaRender(getMemDC(), _alpha);

		break;

	case 3:
		IMAGEMANAGER->findImage("2_4")->alphaRender(getMemDC(), _alpha);
		break;

	case 4:
		IMAGEMANAGER->findImage("2_5")->alphaRender(getMemDC(), _alpha);
		break;

	case 5:
		IMAGEMANAGER->findImage("2_6")->alphaRender(getMemDC(), _alpha);
		break;

	case 6:
		IMAGEMANAGER->findImage("2_7")->alphaRender(getMemDC(), _alpha);
		break;

	case 7:
		IMAGEMANAGER->findImage("2_8")->alphaRender(getMemDC(), _alpha);
		break;

	case 8:
		IMAGEMANAGER->findImage("2_9")->alphaRender(getMemDC(), _alpha);
		break;

	case 9:
		IMAGEMANAGER->findImage("2_2")->alphaRender(getMemDC(), _alpha);
		break;

	case 10:
		IMAGEMANAGER->findImage("2_10")->alphaRender(getMemDC(), _alpha);
		_tick = 0;
		break;

	case 11:
		if (_alpha < 255)_alpha++;
		IMAGEMANAGER->findImage("2_1")->alphaRender(getMemDC(), _alpha);
		IMAGEMANAGER->findImage("버몬트살라딘엔딩")->frameRender(getMemDC(), x, y, _frame, 0);
		if (_frame == 5)
		{
			_bigImageAlpha += 2;
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
			if (_bigImageAlpha >= 255)
			{
				_bigImageAlpha = 255;
				_count++;
			}
		}
		break;

	case 12:
		IMAGEMANAGER->findImage("3_1")->alphaRender(getMemDC(), _alpha);
		if (!_diaSound[3])
		{
			_diaSound.set(3, 1);
			SOUNDMANAGER->play("살라딘좋은왕", 1.0f);
		}
		break;

	case 13:
		IMAGEMANAGER->findImage("4_1")->alphaRender(getMemDC(), _alpha);

		break;

	case 14:
		IMAGEMANAGER->findImage("4_2")->alphaRender(getMemDC(), _alpha);

		break;

	case 15:
		IMAGEMANAGER->findImage("4_3")->alphaRender(getMemDC(), _alpha);
		break;

	case 16:
		IMAGEMANAGER->findImage("4_4")->alphaRender(getMemDC(), _alpha);
		break;
	case 17:
		SCENEMANAGER->changScene("로딩", "오프닝");

	default:
		break;
	}


	// 다음 카운터 넘기기
	if (_count > 0 && _count < 11)
	{
		if (_alpha < 255)
		{
			_alpha += 2;
			_bigImageAlpha -= 2;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			if (_alpha >= 255)_alpha = 255;
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
		}

		if (_alpha >= 255)
		{
			_bigImageAlpha += 2;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
		}

		if (_alpha >= 255 && _bigImageAlpha >= 255)
		{
			_alpha = 0;
			_bigImageAlpha = 255;
			_count++;
		}
	}


	if (_count == 12)
	{
		if (SOUNDMANAGER->getPosition("울음") < 3000)
		{
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
			_bigImageAlpha -= 2;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

		}


		if (SOUNDMANAGER->getLength("살라딘좋은왕") == SOUNDMANAGER->getPosition("살라딘좋은왕"))
		{
			if (!_diaSound[4])
			{
				_diaSound.set(4, 1);
				SOUNDMANAGER->play("울음", 0.1f);
			}

			if (SOUNDMANAGER->getPosition("울음") >= 3000)
			{
				IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
				_bigImageAlpha++;
				if (_bigImageAlpha >= 255)
				{
					_bigImageAlpha = 255;
					_tick = 0;
					_count++;
					_alpha = 0;
				}
			}
		}

	}

	if (_count > 12)
	{
		if (_alpha < 255)
		{
			_alpha += 2;
			_bigImageAlpha -= 2;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			if (_alpha >= 255)_alpha = 255;
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
		}

		if (_alpha >= 255)
		{
			_bigImageAlpha += 1;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
			IMAGEMANAGER->findImage("하얀알파")->alphaRender(getMemDC(), _bigImageAlpha);
		}

		if (_alpha >= 255 && _bigImageAlpha >= 255)
		{
			_alpha = 0;
			_bigImageAlpha = 255;
			_count++;
		}


	}
}

