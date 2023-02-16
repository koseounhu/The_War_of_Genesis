#include "Stdafx.h"
#include "Battle3.h"

#define CAMSPEED 5.0f
#define TURNCAM 10.0f
#define MOVESPEED 2.0f

HRESULT Battle3::init(void)
{
	// 배경
	_bg.x = 0;
	_bg.y = 0;
	_mouseTileFrame = 0;
	_end = 0;

	// UI
	_ui = new UI;
	_ui->init();


	// 턴
	_turn.reset();
	_turnFrame = 0;

	//카메라
	_cam.x = WINSIZE_X / 2;
	_cam.y = WINSIZE_Y / 2;
	_cam.rc = RectMakeCenter(_cam.x, _cam.y, 10, 10);
	_cam.center.reset();


#pragma region 맵, A*
	// 타일 배열 초기화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			_tile[i][j] = { i * WIDTH, j * HEIGHT, i, j, false, false, 0 };
		}
	}

	// 배경 픽셀 이미지에 따라 타일 맵 충돌 여부 초기화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("배틀3픽충배경")->getMemDC(),
				_tile[i][j].x, _tile[i][j].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255)
			{
				_tile[i][j].unit = 2;
			}
		}
	}

	// Object
	_obj.push_back({ 23,  19});
	_obj.push_back({ 35,  19});
	_obj.push_back({ 23,  40});
	_obj.push_back({ 35,  40});


#pragma endregion
#pragma region UNIT

	_pl = new Player;
	_pl->init();
	_pl->setPX(_tile[5][26].x);
	_pl->setPY(_tile[5][26].y);
	_pl->setPView(1);



	for (int i = 0; i < _countof(_em); i++)
	{
		_em[i] = new Enemy2;
		_em[i]->init();
	}
#pragma region 적 최초 좌표 설정
	_em[0]->setIdx(26, 28);
	_em[1]->setIdx(34, 17);
	_em[2]->setIdx(13, 21);
	_em[3]->setIdx(22, 27);
	_em[4]->setIdx(14,34);
	_em[5]->setIdx(22,20);
	_em[6]->setIdx(38,20);
	_em[7]->setIdx(46,35);
	_em[8]->setIdx(21,37);
	_em[9]->setIdx(40,27);
#pragma endregion
	for (int i = 0; i < _countof(_em); i++)
	{
		// _em[i]->setIdx(25, 25);
		_em[i]->setState(0);
		_em[i]->setView(0);
		_tile[_em[i]->getEm().indexX][_em[i]->getEm().indexY].unit = 2;
		_em[i]->setAstar(false);
		_em[i]->setX(_tile[_em[i]->getEm().indexX][_em[i]->getEm().indexY].x);
		_em[i]->setY(_tile[_em[i]->getEm().indexX][_em[i]->getEm().indexY].y);
	}

	// skill
	_da = new Dragon;
	_da->init();

#pragma endregion

	SOUNDMANAGER->play("3번전투배경", 0.3f);
	return S_OK;
}

void Battle3::release(void)
{
	SAFE_DELETE(_pl);
	SAFE_DELETE(_ui);
	SAFE_DELETE(_da);
	
	for (int i = 0; i < _countof(_em); i++)
	{
		SAFE_DELETE_ARRAY(_em[i]);
	}
	
}

void Battle3::update(void)
{
	// 사운드
	if (!SOUNDMANAGER->isPlaySound("3번전투배경")) SOUNDMANAGER->play("3번전투배경", 0.3f);

	// 전체 틱
	_tick++;

	// 마우스타일 프레임
	if (_tick % 10 == 0) _mouseTileFrame++;
	if (_mouseTileFrame > IMAGEMANAGER->findImage("마우스타일")->getMaxFrameX())_mouseTileFrame = 0;

#pragma region 화면제어

	// 마우스로 화면 움직임
	if (_ptMouse.x > WINSIZE_X - 50 && _bg.x > -1220)
	{
		_bg.x -= CAMSPEED;
		_pl->setPX(_pl->getPL()._x - CAMSPEED);
		for (int i = 0; i < _countof(_em); i++)
		{
			_em[i]->setX(_em[i]->getEm().x - CAMSPEED);
		}
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				_tile[i][j].x -= CAMSPEED;
			}
		}
		
	}
	if (_ptMouse.x < 50 && _bg.x < 0)
	{
		_bg.x += CAMSPEED;
		_pl->setPX(_pl->getPL()._x + CAMSPEED);
		for (int i = 0; i < _countof(_em); i++)
		{
			_em[i]->setX(_em[i]->getEm().x + CAMSPEED);
		}
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				_tile[i][j].x += CAMSPEED;
			}
		}
		
	}
	if (_ptMouse.y > WINSIZE_Y - 50 && _bg.y > -650)
	{
		_bg.y -= CAMSPEED;
		_pl->setPY(_pl->getPL()._y - CAMSPEED);
		for (int i = 0; i < _countof(_em); i++)
		{
			_em[i]->setY(_em[i]->getEm().y - CAMSPEED);
		}
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				_tile[i][j].y -= CAMSPEED;
			}
		}
		
	}
	if (_ptMouse.y < 50 && _bg.y < -100)
	{
		_bg.y += CAMSPEED;
		_pl->setPY(_pl->getPL()._y + CAMSPEED);
		for (int i = 0; i < _countof(_em); i++)
		{
			_em[i]->setY(_em[i]->getEm().y + CAMSPEED);
		}
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				_tile[i][j].y += CAMSPEED;
			}
		}
		
	}

	// 시작시 움직임
	if (!_gameStart)
	{
		if (_bg.x > -1220 && _bg.y >= 0)
		{
			_bg.x -= CAMSPEED;
			_pl->setPX(_pl->getPL()._x - CAMSPEED);
			for (int i = 0; i < _countof(_em); i++)
			{
				_em[i]->setX(_em[i]->getEm().x - CAMSPEED);
			}
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x -= CAMSPEED;
				}
			}
			
		}

		else if (_bg.y >-370)
		{
			_bg.y -= CAMSPEED;
			_pl->setPY(_pl->getPL()._y - CAMSPEED);
			for (int i = 0; i < _countof(_em); i++)
			{
				_em[i]->setY(_em[i]->getEm().y - CAMSPEED);
			}
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].y -= CAMSPEED;
				}
			}

			
		}
		else if (_bg.x < 0 && _bg.y < 0)
		{
			_bg.x += CAMSPEED;
			_pl->setPX(_pl->getPL()._x + CAMSPEED);
			for (int i = 0; i < _countof(_em); i++)
			{
				_em[i]->setX(_em[i]->getEm().x + CAMSPEED);
			}
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x += CAMSPEED;
				}
			}

			
		}

		else _gameStart = true;
	}
#pragma endregion

#pragma region UNIT
#pragma region 플레이어
	// 에이스타에 따른 플레이어 움직임
	if (!_turn[15])
	{
		if (_pl->getPL()._astar && _closeList.size() != 0)
		{
			if (_pl->getPL()._indexX < _closeList[_pl->getPL()._xCount].idxX)
			{
				_pl->setPState(1);
				_pl->setPView(1);
				_pl->setPX(_pl->getPL()._x + MOVESPEED);
			}
			else if (_pl->getPL()._indexX > _closeList[_pl->getPL()._xCount].idxX)
			{
				_pl->setPState(1);
				_pl->setPView(0);
				_pl->setPX(_pl->getPL()._x - MOVESPEED);
			}
			else if (_pl->getPL()._indexY < _closeList[_pl->getPL()._yCount].idxY)
			{
				_pl->setPState(1);
				_pl->setPView(2);
				_pl->setPY(_pl->getPL()._y + MOVESPEED);
			}
			else if (_pl->getPL()._indexY > _closeList[_pl->getPL()._yCount].idxY)
			{
				_pl->setPState(1);
				_pl->setPView(3);
				_pl->setPY(_pl->getPL()._y - MOVESPEED);
			}

			if (_pl->getPL()._indexX == _closeList[_pl->getPL()._xCount].idxX &&
				_pl->getPL()._indexY == _closeList[_pl->getPL()._yCount].idxY)
			{
				_pl->setPcount(_pl->getPL()._xCount + 1, _pl->getPL()._yCount + 1);
			}

			if (_pl->getPL()._indexX == _closeList.back().idxX &&
				_pl->getPL()._indexY == _closeList.back().idxY)
			{
				for (int i = 0; i < _closeList.size(); i++)
				{
					_tile[_closeList[i].idxX][_closeList[i].idxY].unit = 0;
				}
				_pl->setPAstar(false);
				_pl->setPIndex(_closeList.back().idxX, _closeList.back().idxY);
				_pl->setPcount(0, 0);
				_pl->setPState(0);
			}

		}
	}

	// 플레이어 인덱스변화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			if (_pl->getPL()._x == _tile[i][j].x &&
				_pl->getPL()._y == _tile[i][j].y)
			{
				_pl->setPIndex(i, j);
				_tile[i][j].unit = 1;
				break;
			}
		}
	}

#pragma endregion 플레이어

#pragma region 적
	// 에이스타에 따른 움직임 / 0~9번 적턴 , 15번 플레이어턴
	for (int i = 0; i < _countof(_em); i++)
	{
		if (_turn[i])
		{
			if (_em[i]->getEm().astar && _closeList.size() != 0)
			{
				if (_em[i]->getEm().indexX < _closeList[_em[i]->getEm().xCount].idxX)
				{
					_em[i]->setState(1);
					_em[i]->setView(1);
					_em[i]->setX(_em[i]->getEm().x + MOVESPEED);
				}
				else if (_em[i]->getEm().indexX > _closeList[_em[i]->getEm().xCount].idxX)
				{
					_em[i]->setState(1);
					_em[i]->setView(0);
					_em[i]->setX(_em[i]->getEm().x - MOVESPEED);
				}
				else if (_em[i]->getEm().indexY < _closeList[_em[i]->getEm().yCount].idxY)
				{
					_em[i]->setState(1);
					_em[i]->setView(3);
					_em[i]->setY(_em[i]->getEm().y + MOVESPEED);

				}
				else if (_em[i]->getEm().indexY > _closeList[_em[i]->getEm().yCount].idxY)
				{
					_em[i]->setState(1);
					_em[i]->setView(2);
					_em[i]->setY(_em[i]->getEm().y - MOVESPEED);
				}

				if (_em[i]->getEm().indexX == _closeList[_em[i]->getEm().xCount].idxX &&
					_em[i]->getEm().indexY == _closeList[_em[i]->getEm().yCount].idxY)
				{
					_em[i]->setCount(_em[i]->getEm().xCount + 1, _em[i]->getEm().yCount + 1);
				}

				// astar 끝
				if (_closeList.size() >= 7)
				{
					if (_em[i]->getEm().indexX == _closeList[6].idxX &&
						_em[i]->getEm().indexY == _closeList[6].idxY)
					{
						for (int i = 0; i < _closeList.size(); i++)
						{
							_tile[_closeList[i].idxX][_closeList[i].idxY].unit = 0;
						}
						_em[i]->setAstar(false);
						_em[i]->setIdx(_closeList[6].idxX, _closeList[6].idxY);
						_em[i]->setCount(0, 0);
						_em[i]->setState(0);
						_turn.set(i , 0);
						_cam.center.set(i + 1, 1);
					}
				}
				else
				{
					if (_em[i]->getEm().indexX == _closeList.back().idxX &&
						_em[i]->getEm().indexY == _closeList.back().idxY)
					{
						for (int i = 0; i < _closeList.size(); i++)
						{
							_tile[_closeList[i].idxX][_closeList[i].idxY].unit = 0;
						}
						_em[i]->setAstar(false);
						_em[i]->setIdx(_closeList.back().idxX, _closeList.back().idxY);
						_em[i]->setCount(0, 0);
						_em[i]->setState(0);
						_turn.set(i , 0);
						_cam.center.set(i + 1, 1);
					}
				}
			}//움직임
		}// 턴
	}// for문


	// 인덱스변화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			for (int k = 0; k < _countof(_em); k++)
			{
				if (_em[k]->getEm().x == _tile[i][j].x &&
					_em[k]->getEm().y == _tile[i][j].y)
				{
					_em[k]->setIdx(i, j);
					_tile[i][j].unit = 1;
					break;
				}
			}
			
		}
	}


#pragma endregion 적

#pragma endregion

#pragma region 카메라
	if (_cam.start)
	{
		for (int i = 0; i < _cam.center.size()-1; i++)
		{
			if (_cam.center[i])
			{		
				// 좌우
				if (_cam.x < _em[i]->getEm().x)
				{
					_bg.x -= CAMSPEED;
					_pl->setPX(_pl->getPL()._x - CAMSPEED);
					for (int i = 0; i < _countof(_em); i++)
					{
						_em[i]->setX(_em[i]->getEm().x - CAMSPEED);
					}
					for (int j = 0; j < V_NUM; j++)
					{
						for (int i = 0; i < H_NUM; i++)
						{
							_tile[i][j].x -= CAMSPEED;
						}
					}
				}
				else if (_cam.x > _em[i]->getEm().x)
				{
					_bg.x += CAMSPEED;
					_pl->setPX(_pl->getPL()._x + CAMSPEED);
					for (int i = 0; i < _countof(_em); i++)
					{
						_em[i]->setX(_em[i]->getEm().x + CAMSPEED);
					}
					for (int j = 0; j < V_NUM; j++)
					{
						for (int i = 0; i < H_NUM; i++)
						{
							_tile[i][j].x += CAMSPEED;
						}
					}
				}

				// 상하
				if (_cam.y < _em[i]->getEm().y)
				{
					_bg.y -= CAMSPEED;
					_pl->setPY(_pl->getPL()._y - CAMSPEED);
					for (int i = 0; i < _countof(_em); i++)
					{
						_em[i]->setY(_em[i]->getEm().y - CAMSPEED);
					}
					for (int j = 0; j < V_NUM; j++)
					{
						for (int i = 0; i < H_NUM; i++)
						{
							_tile[i][j].y -= CAMSPEED;
						}
					}
				}
				else if (_cam.y > _em[i]->getEm().y)
				{
					_bg.y += CAMSPEED;
					_pl->setPY(_pl->getPL()._y + CAMSPEED);
					for (int i = 0; i < _countof(_em); i++)
					{
						_em[i]->setY(_em[i]->getEm().y + CAMSPEED);
					}
					for (int j = 0; j < V_NUM; j++)
					{
						for (int i = 0; i < H_NUM; i++)
						{
							_tile[i][j].y += CAMSPEED;
						}
					}
				}

				// 캐릭터와 충돌
				RECT temp;
				RECT ve = RectMakeCenter(_em[i]->getEm().x, _em[i]->getEm().y, 30, 30);
				if (IntersectRect(&temp, &_cam.rc, &ve))
				{
					_cam.center[i] = false;
					_turn.set(i, 1);
				}
			}
		}
		

		if (_cam.center[10])
		{
			cout << 1 << endl;

			// 좌우
			if (_cam.x < _pl->getPL()._x)
			{
				_bg.x -= CAMSPEED;
				_pl->setPX(_pl->getPL()._x - CAMSPEED);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setX(_em[i]->getEm().x - CAMSPEED);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x -= CAMSPEED;
					}
				}
			}
			else if (_cam.x > _pl->getPL()._x)
			{
				_bg.x += CAMSPEED;
				_pl->setPX(_pl->getPL()._x + CAMSPEED);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setX(_em[i]->getEm().x + CAMSPEED);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x += CAMSPEED;
					}
				}
			}

			// 상하
			if (_cam.y < _pl->getPL()._y)
			{
				_bg.y -= CAMSPEED;
				_pl->setPY(_pl->getPL()._y - CAMSPEED);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setY(_em[i]->getEm().y - CAMSPEED);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].y -= CAMSPEED;
					}
				}
			}
			else if (_cam.y > _pl->getPL()._y)
			{
				_bg.y += CAMSPEED;
				_pl->setPY(_pl->getPL()._y + CAMSPEED);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setY(_em[i]->getEm().y + CAMSPEED);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].y += CAMSPEED;
					}
				}
			}

			// 캐릭터와 충돌
			RECT temp;
			RECT pl = RectMakeCenter(_pl->getPL()._x, _pl->getPL()._y, 30, 30);
			if (IntersectRect(&temp, &_cam.rc, &pl))
			{
				
				_cam.start = false;
				_cam.center.reset();
				_turn.reset();
			}
		}
	}


#pragma endregion

#pragma region 턴

	// 턴 넘기기( 플레이어 -> 적 )
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_cam.start)
		{
			_cam.start = true;
			_cam.center.set(0, 1);
		}

		else if (_cam.start)_cam.start = false;
	}


	// 턴 표시 UI
	if (_tick% 3 == 0)
	{
		_turnFrame++;
		if (_turnFrame > IMAGEMANAGER->findImage("살라딘턴")->getMaxFrameX()) _turnFrame = 0;
	}

	
	for (int i = 0; i < _countof(_em); i++)
	{
		// 공격중
		if (_em[i]->getEm().state == 2)
		{
			if (_em[i]->getEm().atkFrame>=11)
			{
				_pl->setPState(0);
				_turn.set(i, 0);
				_turn.set(i + 1, 1);
				_cam.center.set(i, 0);
				_cam.center.set(i+1, 1);
			}
			break;
		}

		// 대기중
		if (_turn[i] && !_em[i]->getEm().astar)
		{
			// 공격가능 위치에 갔으면 공격
			if (((_em[i]->getEm().indexX == _pl->getPL()._indexX - 2 || _em[i]->getEm().indexX == _pl->getPL()._indexX + 2) && _em[i]->getEm().indexY == _pl->getPL()._indexY) ||
				(_em[i]->getEm().indexX == _pl->getPL()._indexX && (_em[i]->getEm().indexY == _pl->getPL()._indexY - 2 || _em[i]->getEm().indexY == _pl->getPL()._indexY + 2)))
			{
				if (_em[i]->getEm().indexY == _pl->getPL()._indexY)
				{
					_pl->setPState(4);
					_em[i]->setState(2);
					int sta = _pl->getPL()._indexX - _em[i]->getEm().indexX;
					switch (sta)
					{
					case 2:
						_em[i]->setView(1);
						_pl->setPView(0);
						break;

					case -2:
						_em[i]->setView(0);
						_pl->setPView(1);
						break;

					default:
						break;
					}
					break;
				}
				if (_em[i]->getEm().indexX == _pl->getPL()._indexX)
				{
					_pl->setPState(4);
					_em[i]->setState(2);
					int sta = _pl->getPL()._indexY - _em[i]->getEm().indexY;
					switch (sta)
					{
					case 2:
						_em[i]->setView(3);
						_pl->setPView(3);
						break;

					case -2:
						_em[i]->setView(2);
						_pl->setPView(2);
						break;

					default:
						break;
					}
					break;
				}
			}
			
			// 플레이어 주변이 비었으면
			else if (_tile[_pl->getPL()._indexX - 2][_pl->getPL()._indexY].unit == 0 ||
				_tile[_pl->getPL()._indexX + 2][_pl->getPL()._indexY].unit == 0||
				_tile[_pl->getPL()._indexX ][_pl->getPL()._indexY-2].unit == 0 ||
				_tile[_pl->getPL()._indexX ][_pl->getPL()._indexY+2].unit == 0)
			{
				// 플레이어 근처가 아니면 a스타 발동
				if ((_em[i]->getEm().indexX != _pl->getPL()._indexX - 2 || _em[i]->getEm().indexX != _pl->getPL()._indexX + 2) &&
					(_em[i]->getEm().indexY != _pl->getPL()._indexY - 2 || _em[i]->getEm().indexY != _pl->getPL()._indexY + 2))
				{
					if (_tile[_pl->getPL()._indexX - 2][_pl->getPL()._indexY].unit == 0)
						Astar(_em[i]->getEm().indexX, _em[i]->getEm().indexY, _pl->getPL()._indexX - 2, _pl->getPL()._indexY);
						
					if (_tile[_pl->getPL()._indexX + 2][_pl->getPL()._indexY].unit == 0)
						Astar(_em[i]->getEm().indexX, _em[i]->getEm().indexY, _pl->getPL()._indexX + 2, _pl->getPL()._indexY);

					if (_tile[_pl->getPL()._indexX][_pl->getPL()._indexY-2].unit == 0)
						Astar(_em[i]->getEm().indexX, _em[i]->getEm().indexY, _pl->getPL()._indexX, _pl->getPL()._indexY-2);

					if (_tile[_pl->getPL()._indexX][_pl->getPL()._indexY+2].unit == 0)
						Astar(_em[i]->getEm().indexX, _em[i]->getEm().indexY, _pl->getPL()._indexX, _pl->getPL()._indexY+2);

					// 에이스타 시작
					if (_closeList.size() > 0)	_em[i]->setAstar(true);
				}
			}

			// 아무것도 해당안됨
			else
			{
				_turn.set(i, 0);
				_turn.set(i+1, 1);
				_cam.center.set(i, 0);
				_cam.center.set(i + 1, 1);
			}

			break;// 발동시키고 탈출
		}// 턴
		

	}// for문
#pragma endregion


	// 플레이어 UI 띄우기
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		SOUNDMANAGER->play("버튼", 1.0f);
		if (!_ui->getTotalUI())
		{
			// 플레이어 렉트
			RECT _temp;
			_temp = RectMake(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].x,
				_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].y,
				WIDTH, HEIGHT);
			if (PtInRect(&_temp, _ptMouse))
			{
				_ui->setUIState(true);
			}
		}
	}

	// 객체 업데이트
	_pl->update();
	_ui->update();
	for (int i = 0; i < _countof(_em); i++)
	{
		_em[i]->update();
	}

	// 스킬 스타트
	if (_ui->getDragonState())
	{
		// 스킬구
		if (_da->getPhase() == 0)
		{
			_pl->setPState(3);
			_pl->setPSkill(0);
		}
		if (_da->getPhase() >= 1)
		{
			if (_tick % 5 == 0)
			{
				_pl->setPSkill(_pl->getPL().skill + 1);
			}
		}


		// 스킬끝
		if (_da->getPhase() == 4)
		{
			_pl->setPSkill(0);
			_pl->setPState(0);
			_ui->setDragonState(false);
			for (int i = 0; i < _countof(_em); i++)
			{
				_em[i]->setState(4);		// 스킬피격되어 알파값으로 없어지는 상태
			}
		}

		// 마지막 폭발시 카메라 쉐이킹
		if (_da->getPhase() == 3)
		{
			if (_tick % 5 == 0)
			{
				if (_shaking) _shaking = false;
				else _shaking = true;
			}

			if (_shaking)
			{
				_bg.x -=2;
				_pl->setPX(_pl->getPL()._x -2);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setX(_em[i]->getEm().x -2);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x -=2;
					}
				}
			}
			else
			{
				_bg.x +=2;
				_pl->setPX(_pl->getPL()._x +2);
				for (int i = 0; i < _countof(_em); i++)
				{
					_em[i]->setX(_em[i]->getEm().x +2);
				}
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x +=2;
					}
				}
			}
		}

		_da->setPl(_pl->getPL()._x, _pl->getPL()._y, false);				// 플레이어 좌표 실시간 업데이트
		
		for (int i = 0; i < _countof(_em); i++)
		{
			if (!_dragon)													// 배틀씬에서 판정해주는 불값
			{
				_da->pushEM(_em[i]->getEm().x, _em[i]->getEm().y, false);		// 최초 1회 적 좌표 설정
			}

			_da->setEm(i, _em[i]->getEm().x, _em[i]->getEm().y, false);		// 적 좌표 실시간 업데이트
		}
		_dragon = true;														// 반복문 1회 돌고나면 다음부터는 벡터에 삽입 안되게 바꿔줌
		_da->update();		


	}

	
}

void Battle3::render(void)
{
	// 배경
	IMAGEMANAGER->findImage("전투맵3")->render(getMemDC(),_bg.x,_bg.y);
	// 스킬 시작시
	if(_ui->getDragonState())	IMAGEMANAGER->findImage("검정알파")->render(getMemDC());


	// 임시 마우스 좌표
	// for (int i = 0; i < H_NUM; i++)
	// {
	// 	for (int j = 0; j < V_NUM; j++)
	// 	{
	// 		if ((_ptMouse.x > _tile[i][j].x && _ptMouse.x < _tile[i + 1][j].x) &&
	// 			(_ptMouse.y > _tile[i][j].y && _ptMouse.y < _tile[i][j+1].y))
	// 		{
	// 			cout << i << "," << j << endl;
	// 			DrawRectMake(getMemDC(), RectMake(_tile[i][j].x, _tile[i][j].y, 40, 32));
	// 		}
	// 	}
	// }


#pragma region 타일온

	if (_ui->getTileState())
	{
		moveTileStar(_pl->getPL()._indexX, _pl->getPL()._indexY);
		for (int i = 0; i < V_NUM; i++)
		{
			for (int j = 0; j < H_NUM; j++)
			{
				if (_tile[j][i].moveTileColli)
				{
					IMAGEMANAGER->findImage("블루타일")->alphaRender(getMemDC(), _tile[j][i].x, _tile[j][i].y, 100);
				}
			}
		}
		for (int i = 0; i < _cantMoveList.size(); i++)
		{
			IMAGEMANAGER->findImage("노랑타일")->alphaRender(getMemDC(), _tile[_cantMoveList[i].idxX][_cantMoveList[i].idxY].x,
				_tile[_cantMoveList[i].idxX][_cantMoveList[i].idxY].y, 100);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("버튼", 1.0f);

			// 플레이어이동
			if (_ui->getTileState())
			{
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						// 클릭에 따른 A* 활성화
						if (_ptMouse.x > _tile[i][j].x && _ptMouse.x < _tile[i + 1][j].x &&
							_ptMouse.y > _tile[i][j].y && _ptMouse.y < _tile[i][j + 1].y)
						{
							if (!_tile[i][j].mapColli)
							{
								Astar(_pl->getPL()._indexX, _pl->getPL()._indexY, i, j);
								_pl->setPAstar(true);
							}
						}
					}
				}
			}
			_ui->setTileState(false);
		}
	}
#pragma endregion
#pragma region 마우스타일, 맵타일그리기
	// 마우스타일
	for (int j = 0; j < H_NUM; j++)
	{
		for (int i = 0; i < V_NUM; i++)
		{
			if (_tile[j][i].x < _ptMouse.x && _tile[j][i].y < _ptMouse.y &&
				_tile[j + 1][i].x > _ptMouse.x && _tile[j][i + 1].y > _ptMouse.y)
			{
				IMAGEMANAGER->findImage("마우스타일")->alphaFrameRender(getMemDC(),
					_tile[j][i].x, _tile[j][i].y, 150, _mouseTileFrame, 0);
			}

		}
	}

	// 각 구획마다 선 그리기
	if (KEYMANAGER->isToggleKey(VK_F10))
	{
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				// 좌상 -> 우상
				LineMake(getMemDC(), _tile[i][j].x, _tile[i][j].y,
					_tile[i][j].x + WIDTH, _tile[i][j].y);
				// 좌상 -> 좌하
				LineMake(getMemDC(), _tile[i][j].x, _tile[i][j].y,
					_tile[i][j].x, _tile[i][j].y + HEIGHT);
				// 우하 -> 우상
				LineMake(getMemDC(), _tile[i][j].x + WIDTH, _tile[i][j].y + HEIGHT,
					_tile[i][j].x + WIDTH, _tile[i][j].y);
				// 우하 -> 좌하
				LineMake(getMemDC(), _tile[i][j].x + WIDTH, _tile[i][j].y + HEIGHT,
					_tile[i][j].x, _tile[i][j].y + HEIGHT);
			}
		}
	}
#pragma endregion


	// 임시 이동타일 보이기
	if (_closeList.size() > 0)
	{
		for (int i = 0; i < _closeList.size(); i++)
		{
			DrawRectMake(getMemDC(), RectMake(_tile[_closeList[i].idxX][_closeList[i].idxY].x,
				_tile[_closeList[i].idxX][_closeList[i].idxY].y, 40, 32));
		}
	}

	//  플레이어 일반공격
	if (_ui->getAtkTile())
	{
		IMAGEMANAGER->findImage("오랑타일")->alphaRender(getMemDC(), _pl->getPL()._x - 80, _pl->getPL()._y, 100);
		IMAGEMANAGER->findImage("오랑타일")->alphaRender(getMemDC(), _pl->getPL()._x + 80, _pl->getPL()._y, 100);
		IMAGEMANAGER->findImage("오랑타일")->alphaRender(getMemDC(), _pl->getPL()._x, _pl->getPL()._y - 64, 100);
		IMAGEMANAGER->findImage("오랑타일")->alphaRender(getMemDC(), _pl->getPL()._x, _pl->getPL()._y + 64, 100);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("버튼", 1.0f);
			_pl->setPState(2);

			// 주변 4명 동시공격
			/*
			for (int i = 0; i < _countof(_em); i++)
			{
				if (((_em[i]->getEm().indexX == _pl->getPL()._indexX - 2 || _em[i]->getEm().indexX == _pl->getPL()._indexX + 2)&& _em[i]->getEm().indexY == _pl->getPL()._indexY)||
					(_em[i]->getEm().indexX == _pl->getPL()._indexX && (_em[i]->getEm().indexY == _pl->getPL()._indexY - 2 || _em[i]->getEm().indexY == _pl->getPL()._indexY + 2)))
				{
					int view = _pl->getPL()._indexX - _em[i]->getEm().indexX;
					int updown = _pl->getPL()._indexY - _em[i]->getEm().indexY;
					_pl->setPState(2);
					_em[i]->setState(3);

					switch (view)
					{
					case 2:
						_pl->setPView(0);		// 좌
						_em[i]->setView(1);
						break;

						
					case -2:
						_pl->setPView(1);		// 우
						_em[i]->setView(0);
						break;
					
					case 0:
						// 상
						if (updown == 2) 
						{
							_pl->setPView(3);	// 상
							_em[i]->setView(3);
						}
						// 하
						else if (updown == -2)
						{
							_pl->setPView(2);	// 하
							_em[i]->setView(2);
						}

						break;

					default:
						break;
					}
				}
			}

			_ui->setAtkTile(false);

		*/

			// 플레이어 -> 적 공격
			for (int j = 0; j < H_NUM; j++)
			{
				for (int i = 0; i < V_NUM; i++)
				{
					for (int k = 0; k < _countof(_em); k++)
					{
						if ((_ptMouse.x > _tile[i][j].x && _ptMouse.x < _tile[i + 1][j].x && _ptMouse.y > _tile[i][j].y && _ptMouse.y < _tile[i][j + 1].y) &&
							(_tile[i][j].x == _em[k]->getEm().x && _tile[i][j].y == _em[k]->getEm().y))
						{
							_em[k]->setState(3);

							int viewX = _pl->getPL()._indexX - _em[k]->getEm().indexX;
							int viewY = _pl->getPL()._indexY - _em[k]->getEm().indexY;
							switch (viewX)
							{
							case 2:
								_em[k]->setView(1);
								_pl->setPView(0);
								break;

							case -2:
								_em[k]->setView(0);
								_pl->setPView(1);
								break;

							case 0:
								switch (viewY)
								{
								case 2:
									_em[k]->setView(3);
									_pl->setPView(3);
									break;

								case -2:
									_em[k]->setView(2);
									_pl->setPView(2);
									break;

								default:
									break;
								}


								break;

							default:
								break;
							}

							
						}
					}
					
				}
			}
			_ui->setAtkTile(false);
		}
	}

	
	// 순서에 따른 렌더링
	renerOrder();

	// 턴 표시 UI
	for (int i = 0; i < _turn.size(); i++)
	{
		if (_turn[i])
			IMAGEMANAGER->findImage("적턴")->frameRender(getMemDC(), _em[i]->getEm().x + 12, _em[i]->getEm().y - 60, _turnFrame, 0);
	}
	if (_turn.any()==0)
		IMAGEMANAGER->findImage("살라딘턴")->frameRender(getMemDC(), _pl->getPL()._x + 17, _pl->getPL()._y - 70, _turnFrame, 0);


	IMAGEMANAGER->findImage("MapInfo")->render(getMemDC(), 790, 5);
	FONTMANAGER->drawText(getMemDC(), 880, 20, 15, 255, 255, 255, "굴림", false, "술탄궁 내부");
	FONTMANAGER->drawText(getMemDC(), 950, 45, 15, 255, 255, 255, "굴림", true, "평  지");
	FONTMANAGER->drawInt(getMemDC(), 940, 85, 15, 255, 255, 255, "굴림", false, (char*)GOLD->getGold());
	FONTMANAGER->drawText(getMemDC(), 1000, 85, 15, 255, 255, 255, "굴림", false, "eld");
	_ui->render(_pl);


	// 스킬 시작
	if (_ui->getDragonState())
	{
		_da->render();
	}

	if (_em[0]->getDie())
	{
		_end++;
		IMAGEMANAGER->findImage("시나리오클리어")->alphaRender(getMemDC(), 0, 300, 50);
		IMAGEMANAGER->findImage("클리어광원")->alphaRender(getMemDC(), 0, 300, 150);
		IMAGEMANAGER->findImage("클리어텍스트")->alphaRender(getMemDC(), 305, 325, 100);
		IMAGEMANAGER->findImage("클리어텍스트광원")->alphaRender(getMemDC(), 300, 320, 255);
		if (_end > 100)
		{
			_end = 0;
			SCENEMANAGER->changScene("로딩", "전투2");
		}
	}
}

void Battle3::renerOrder(void)
{
	// 초기화
	_renOrder.clear();

	// 플레이어 인덱스 추가
	_renOrder.push_back(make_pair( _pl->getPL()._indexY, _pl->getPL()._indexX ));
	
	// 기둥 추가
	for (int i = 0; i <_obj.size(); i++)
	{
		_renOrder.push_back(make_pair(_obj[i].idxY, _obj[i].idxX));
	}

	// 적 인덱스 추가
	for (int i = 0; i < _countof(_em); i++)
	{
		_renOrder.push_back(make_pair(_em[i]->getEm().indexY,_em[i]->getEm().indexX ));
	}

	// 정렬 
	sort(_renOrder.begin(), _renOrder.end());

	// 렌더
	for (int i = 0; i < _renOrder.size(); i++)
	{
		
		if (_renOrder[i].first == _pl->getPL()._indexY && _renOrder[i].second == _pl->getPL()._indexX)
		{
			_pl->render();
		}

		for (int j = 0; j < 10; j++)
		{
			if (_renOrder[i].first == _em[j]->getEm().indexY && _renOrder[i].second == _em[j]->getEm().indexX)
			{
				_em[j]->render();
			}
		}

		for (int j = 0; j < _obj.size(); j++)
		{
			if (_renOrder[i].first == _obj[j].idxY && _renOrder[i].second == _obj[j].idxX)
			{
				IMAGEMANAGER->findImage("배틀3기둥")->alphaRender(getMemDC(), _tile[_obj[j].idxX][_obj[j].idxY].x-40, _tile[_obj[j].idxX][_obj[j].idxY].y - 220,105);
			}
		}
	}


}
void Battle3::Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY)
{
	// 이동 시 거리 값 초기화
	float moveCost = 1.0f;

	// 출발 위치 초기화
	int _startIdxX;
	int _startIdxY;

	// 타일 A* 체크 초기화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			_tile[i][j].aStarColli = false;
			if (_tile[i][j].unit != 0)
			{
				_tile[i][j].aStarColli = true;
			}
			_tile[i][j].aStarColli = _tile[i][j].mapColli;
		}
	}

	// AStar 종료 초기화
	_aStarBreak = false;

	// 닫힌 목록 삭제
	_closeList.clear();

	// 시작 값 입력
	_startIdxX = startIdxX;
	_startIdxY = startIdxY;

	// 알고리즘 반복
	while (!_aStarBreak)
	{

		// 닫힌 목록에 시작 자리 추가 및 닫기
		_closeList.push_back({ _tile[_startIdxX][_startIdxY].idxX,
			_tile[_startIdxX][_startIdxY].idxY, 0.0f });
		_tile[_startIdxX][_startIdxY].aStarColli = true;

		// 열린 목록 삭제
		_openList.clear();

		// 열린 목록에 좌측 추가
		if (_startIdxX > 0)
		{

			if (!_tile[_startIdxX - 1][_startIdxY].aStarColli &&
				_tile[_startIdxX - 1][_startIdxY].unit == 0)
			{
				_openList.push_back({ _startIdxX - 1, _startIdxY, moveCost,
					sqrt((float)pow(endIdxX - (_startIdxX - 1), 2) +
						(float)pow(endIdxY - _startIdxY, 2)), ASTAR_MAX_COST });
				_tile[_startIdxX - 1][_startIdxY].aStarColli = true;
			}
		}

		// 열린 목록에 우측 추가
		if (_startIdxX < H_NUM - 1)
		{
			if (!_tile[_startIdxX + 1][_startIdxY].aStarColli &&
				_tile[_startIdxX + 1][_startIdxY].unit == 0)
			{
				_openList.push_back({ _startIdxX + 1, _startIdxY, moveCost,
					sqrt((float)pow(endIdxX - (_startIdxX + 1), 2) +
						(float)pow(endIdxY - _startIdxY, 2)), ASTAR_MAX_COST });
				_tile[_startIdxX + 1][_startIdxY].aStarColli = true;
			}
		}

		// 열린 목록에 상측 추가
		if (_startIdxY > 0)
		{
			if (!_tile[_startIdxX][_startIdxY - 1].aStarColli &&
				_tile[_startIdxX][_startIdxY - 1].unit == 0)
			{
				_openList.push_back({ _startIdxX, _startIdxY - 1, moveCost,
					sqrt((float)pow(endIdxX - _startIdxX, 2) +
						(float)pow(endIdxY - (_startIdxY - 1), 2)), ASTAR_MAX_COST });
				_tile[_startIdxX][_startIdxY - 1].aStarColli = true;
			}
		}

		// 열린 목록에 하측 추가
		if (_startIdxY < V_NUM - 1)
		{
			if (!_tile[_startIdxX][_startIdxY + 1].aStarColli &&
				_tile[_startIdxX][_startIdxY + 1].unit == 0)
			{
				_openList.push_back({ _startIdxX, _startIdxY + 1, moveCost,
					sqrt((float)pow(endIdxX - _startIdxX, 2) +
						(float)pow(endIdxY - (_startIdxY + 1), 2)), ASTAR_MAX_COST });
				_tile[_startIdxX][_startIdxY + 1].aStarColli = true;
			}
		}

		// 열린 목록 총 비용 업데이트
		for (int i = 0; i < _openList.size(); i++)
		{
			_openList[i].totalCost = _openList[i].fromStartCost + _openList[i].toEndCost;
		}

		// 종료 조건
		if (_openList.size() == 0) _aStarBreak = true;
		else
		{
			for (int i = 0; i < _openList.size(); i++)
			{
				if (_openList[i].idxX == endIdxX && _openList[i].idxY == endIdxY)
				{
					_closeList.push_back({ endIdxX, endIdxY, 0 });
					_openList.clear();
					_aStarBreak = true;
				}
				else if (_startIdxX == endIdxX && _startIdxY == endIdxY)
				{
					_closeList.push_back({ endIdxX, endIdxY, 0 });
					_openList.clear();
					_aStarBreak = true;
				}
			}
		}


		// 총 비용이 가장 작은 인덱스 값 계산
		int minCostIdx = 0;
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_openList[i].totalCost < _openList[minCostIdx].totalCost)
				minCostIdx = i;
		}

		// 총 비용이 가장 작은 값을 닫힌 목록에 추가
		if (_openList.size() != 0)
		{
			if (_openList[minCostIdx].idxX != _closeList[_closeList.size() - 1].idxX &&
				_openList[minCostIdx].idxY != _closeList[_closeList.size() - 1].idxY)
			{
				_closeList.push_back({ _openList[minCostIdx].idxX, _openList[minCostIdx].idxY,
					_openList[minCostIdx].fromStartCost + 1 });
			}
		}

		// 이동 시 거리 값 업데이트
		moveCost++;

		// 시작 값 업데이트
		if (_openList.size() != 0)
		{
			_startIdxX = _openList[minCostIdx].idxX;
			_startIdxY = _openList[minCostIdx].idxY;
		}
	}







}