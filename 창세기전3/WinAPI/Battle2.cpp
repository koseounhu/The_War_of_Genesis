#include "Stdafx.h"
#include "Battle2.h"


HRESULT Battle2::init(void)
{
#pragma region 화면 충돌렉트
	_rc[0] = RectMake(0, 0, WINSIZE_X, 50);
	_rc[1] = RectMake(0, 0, 50, WINSIZE_Y);
	_rc[2] = RectMake(0, WINSIZE_Y - 50, WINSIZE_X, 50);
	_rc[3] = RectMake(WINSIZE_X - 50, 0, 50, WINSIZE_Y);
	_x = _y = 0;
#pragma endregion

#pragma region 맵, A*
	// 타일 배열 초기화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			_tile[i][j] = { i * WIDTH, j * HEIGHT, i, j, false, false, 0 };
		}
	}
#pragma endregion

	// 임시 플레이어
	_pl = new Player;
	_pl->init();
	_pl->setPX(_tile[19][28].x);
	_pl->setPY(_tile[19][28].y);
	_pl->setPcount(0, 0);


    return S_OK;
}

void Battle2::release(void)
{
}

void Battle2::update(void)
{
#pragma region 시작시 카메라 무빙
	if (!_gameStart)
	{
		if (_x > -250)
		{
			_x -= 3;
			_pl->setPX(_pl->getPL()._x - 3);
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x -= 3;
				}
			}
		}
		else if (_x < -250 && _y > -900)
		{
			_y -= 3;
			_pl->setPY(_pl->getPL()._y - 3);

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].y -= 3;
				}
			}
		}
		else _gameStart = true;
	}

#pragma endregion
#pragma region 화면 움직임 제어

	if (PtInRect(&_rc[3], _ptMouse))
	{
		if (_x > -800)
		{
			_x -= 2;
			_pl->setPX(_pl->getPL()._x - 2);

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x -= 2;
				}
			}
		}

	}
	else if (PtInRect(&_rc[0], _ptMouse))
	{
		if (_y < 0)
		{
			_y += 2;
			_pl->setPY(_pl->getPL()._y +2);

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].y += 2;
				}
			}
		}
	}
	else if (PtInRect(&_rc[1], _ptMouse))
	{
		if (_x < 0)
		{
			_x += 2;
			_pl->setPX(_pl->getPL()._x +2);

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x += 2;
				}
			}
		}
	}
	else if (PtInRect(&_rc[2], _ptMouse))
	{
		if (_y > -900)
		{
			_y -= 2;
			_pl->setPY(_pl->getPL()._y - 2);

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].y -= 2;
				}
			}
		}
	}

#pragma endregion


	// 임시 플레이어
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

	
	_pl->update();


	

	// 에이스타에 따른 플레이어 움직임
	if (_pl->getPL()._astar && _closeList.size() !=0 )
	{
		if (_pl->getPL()._indexX < _closeList[_pl->getPL()._xCount].idxX)
		{
			_pl->setPState(1);
			_pl->setPView(1);
			_pl->setPX(_pl->getPL()._x + 1);
		}
		else if (_pl->getPL()._indexX > _closeList[_pl->getPL()._xCount].idxX)
		{
			_pl->setPState(1);
			_pl->setPView(0);
			_pl->setPX(_pl->getPL()._x - 1);
		}
		else if (_pl->getPL()._indexY < _closeList[_pl->getPL()._yCount].idxY)
		{
			_pl->setPState(1);
			_pl->setPView(2);
			_pl->setPY(_pl->getPL()._y + 1);
		}
		else if (_pl->getPL()._indexY > _closeList[_pl->getPL()._yCount].idxY)
		{
			_pl->setPState(1);
			_pl->setPView(3);
			_pl->setPY(_pl->getPL()._y - 1);
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

	if (KEYMANAGER->isOnceKeyDown(VK_F12))SCENEMANAGER->changScene("월드맵");



}

void Battle2::render(void)
{
	// 배경
	IMAGEMANAGER->findImage("전투맵2")->render(getMemDC(), _x, _y);

	// 마우스 타일
	if(!_ui)
	for (int j = 0; j < H_NUM; j++)
	{
		for (int i = 0; i < V_NUM; i++)
		{
			if (_tile[j][i].x < _ptMouse.x && _tile[j][i].y < _ptMouse.y &&
				_tile[j + 1][i].x > _ptMouse.x && _tile[j][i + 1].y > _ptMouse.y)
			{
				IMAGEMANAGER->findImage("마우스타일")->alphaFrameRender(getMemDC(),
					_tile[j][i].x, _tile[j][i].y, 150, 0, 0);
			}
		}
	}


	// 임시 플레이어
	_pl->render();

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

	// Astar 움직임
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		// 플레이어 렉트
		RECT _temp;
		_temp = RectMake(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].x,
			_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].y,
			WIDTH, HEIGHT);
		if (PtInRect(&_temp, _ptMouse)) _ui = true;


		if (!_ui && !_ability && !_skillOn)
		{
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					// 클릭에 따른 A* 활성화
					if (_ptMouse.x > _tile[i][j].x && _ptMouse.x < _tile[i + 1][j].x &&
						_ptMouse.y > _tile[i][j].y && _ptMouse.y < _tile[i][j + 1].y)
					{
						Astar(_pl->getPL()._indexX, _pl->getPL()._indexY, i, j);
						_pl->setPAstar(true);
					}
				}
			}
		}
		
	}

#pragma region skillUI
	#pragma region
	// 스킬 UI 창
	if (_ui)
	{
		RECT _skillUI[4];
		_skillUI[0]= RectMakeCenter(_pl->getPL()._x-80, _pl->getPL()._y-40, IMAGEMANAGER->findImage("스킬UI")->getFrameWidth(), IMAGEMANAGER->findImage("스킬UI")->getFrameHeight());
		_skillUI[1]= RectMakeCenter(_pl->getPL()._x+130, _pl->getPL()._y-40, IMAGEMANAGER->findImage("스킬UI")->getFrameWidth(), IMAGEMANAGER->findImage("스킬UI")->getFrameHeight());
		_skillUI[2]= RectMakeCenter(_pl->getPL()._x-80, _pl->getPL()._y, IMAGEMANAGER->findImage("스킬UI")->getFrameWidth(), IMAGEMANAGER->findImage("스킬UI")->getFrameHeight());
		_skillUI[3]= RectMakeCenter(_pl->getPL()._x+130, _pl->getPL()._y, IMAGEMANAGER->findImage("스킬UI")->getFrameWidth(), IMAGEMANAGER->findImage("스킬UI")->getFrameHeight());

		

		IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[0].left, _skillUI[0].top, 0, 0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[0].left + 32, _skillUI[0].top + 7, 15, 255, 255, 255, "굴림", true, "어빌리티");

		IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[1].left, _skillUI[1].top,1,0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[1].left+32, _skillUI[1].top+7, 15, 255, 255, 255, "굴림", true, "완전방어");
		IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[2].left, _skillUI[2].top,2,0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[2].left+32, _skillUI[2].top+7, 15, 255, 255, 255, "굴림", true, "아이템");
		IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[3].left, _skillUI[3].top,3,0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[3].left+32, _skillUI[3].top+7, 15, 255, 255, 255, "굴림", true, "상태");

		if (PtInRect(&_skillUI[0], _ptMouse))
		{
			IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[0].left, _skillUI[0].top, 0, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[0].left + 32, _skillUI[0].top + 7, 15, 255, 255, 255, "굴림", true, "어빌리티");

		}

		if (PtInRect(&_skillUI[1], _ptMouse))
		{
			IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[1].left, _skillUI[1].top, 1, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[1].left + 32, _skillUI[1].top + 7, 15, 255, 255, 255, "굴림", true, "완전방어");
		}
		if (PtInRect(&_skillUI[2], _ptMouse))
		{
			IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[2].left, _skillUI[2].top, 2, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[2].left + 32, _skillUI[2].top + 7, 15, 255, 255, 255, "굴림", true, "아이템");
		}
		if (PtInRect(&_skillUI[3], _ptMouse))
		{
			IMAGEMANAGER->findImage("스킬UI")->frameRender(getMemDC(), _skillUI[3].left, _skillUI[3].top, 3, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[3].left + 32, _skillUI[3].top + 7, 15, 255, 255, 255, "굴림", true, "상태");
		}

		if (PtInRect(&_skillUI[0], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_ui = false;
			_ability = true;
		}
	}
	#pragma endregion

	#pragma region 어빌리티
	if (_ability)
	{
		RECT _abilityA;
		_abilityA = RectMakeCenter(_pl->getPL()._x + 50, _pl->getPL()._y - 60, IMAGEMANAGER->findImage("어빌리티창")->getFrameWidth(), IMAGEMANAGER->findImage("어빌리티창")->getFrameHeight());

		IMAGEMANAGER->findImage("어빌리티창")->alphaRender(getMemDC(), _abilityA.left, _abilityA.top,150);
		IMAGEMANAGER->findImage("어빌리티버튼")->frameRender(getMemDC(), _abilityA.left+10, _abilityA.top+10,1,0);
		IMAGEMANAGER->findImage("어빌리티버튼")->frameRender(getMemDC(), _abilityA.left+10, _abilityA.top+35,0,0);
		IMAGEMANAGER->findImage("어빌리티버튼")->frameRender(getMemDC(), _abilityA.left+10, _abilityA.top+60,0,0);


		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 10, 15, 255, 255, 255, "굴림", true, "천지파열무");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 35, 15, 255, 255, 255, "굴림", true, "연");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 60, 15, 255, 255, 255, "굴림", true, "파");

		RECT _abilityB;
		_abilityB = RectMake(_abilityA.left + 5, _abilityA.top + 10, 150, 20);
		DrawRectMake(getMemDC(), _abilityB);
		if (PtInRect(&_abilityB, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_ui = _ability = false;
			_skillOn = true;
		}
	}
	#pragma endregion
#pragma endregion



}


void Battle2::Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY)
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
