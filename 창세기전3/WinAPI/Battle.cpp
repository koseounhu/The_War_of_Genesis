#include "Stdafx.h"
#include "Battle.h"

#define CAMSPEED 9.0f

HRESULT Battle::init(void)
{
#pragma region 
   
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

	// 배경 픽셀 이미지에 따라 타일 맵 충돌 여부 초기화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("픽충배경")->getMemDC(),
				_tile[i][j].x, _tile[i][j].y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) _tile[i][j].unit = 2;
		}
	}
#pragma endregion

#pragma region UNIT
	// 플레이어
	_pl = new Player;
	_pl->init();
	_pl->setPX(_tile[19][45].x);
	_pl->setPY(_tile[19][45].y);
	_pl->setPView(3);
	_pl->setPcount(0, 0);

	_ve = new Vermouth;
	_ve->init();
	_ve->setVEX(_tile[19][21].x);
	_ve->setVEY(_tile[19][21].y);
	_ve->setVEView(2);
	_ve->setVCount(0, 0);

	_sk = new Skill;
	_sk->init();

	_ti = new Tiger;
	_ti->init();


#pragma endregion

	_cam.x = WINSIZE_X / 2;
	_cam.y = WINSIZE_Y / 2;
	_cam.rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 10, 10);

	_x = _y = 0;
	_ui = new UI;
	_ui->init();
	



	SOUNDMANAGER->play("2번전투배경", 0.3f);

    return S_OK;
}

void Battle::release(void)
{
	SAFE_DELETE(_sk);
	SAFE_DELETE(_pl);
	SAFE_DELETE(_ui);
	SAFE_DELETE(_ve);
	SAFE_DELETE(_ti);
}

void Battle::update(void)
{
#pragma region 시작시 카메라 무빙
	if (!_gameStart)
	{
		if (_x > -250)
		{
			_x -= 3;
			_pl->setPX(_pl->getPL()._x - 3);
			_ve->setVEX(_ve->getVE()._x - 3);
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
			_ve->setVEY(_ve->getVE()._y - 3);
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

	if (!_ui->getUIState() && !_pl->getPL()._astar && !_ve->getVE()._astar)
	{

		if (_ptMouse.x > WINSIZE_X - 50)
		{
			if (_x > -570)
			{
				_x -= 2;
				_pl->setPX(_pl->getPL()._x - 2);
				_ve->setVEX(_ve->getVE()._x - 2);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x -= 2;
					}
				}
			}

		}
		else if (_ptMouse.y < 50)
		{
			if (_y < 0)
			{
				_y += 2;
				_pl->setPY(_pl->getPL()._y + 2);
				_ve->setVEY(_ve->getVE()._y + 2);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].y += 2;
					}
				}
			}
		}
		else if (_ptMouse.x < 50)
		{
			if (_x < 0)
			{
				_x += 2;
				_pl->setPX(_pl->getPL()._x + 2);
				_ve->setVEX(_ve->getVE()._x + 2);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x += 2;
					}
				}
			}
		}
		else if (_ptMouse.y > WINSIZE_Y - 50)
		{
			if (_y > -1030)
			{
				_y -= 2;
				_pl->setPY(_pl->getPL()._y - 2);
				_ve->setVEY(_ve->getVE()._y - 2);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].y -= 2;
					}
				}
			}
		}
	}


#pragma endregion
#pragma region 플레이어
	// 에이스타에 따른 플레이어 움직임
	if (_pl->getPL()._astar && _closeList.size() != 0)
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
	_pl->update();
	_sk->update();

#pragma endregion
#pragma region 버몬트
	// 에이스타에 따른 플레이어 움직임
	if (_ve->getVE()._astar && _closeList.size() != 0)
	{
		if (_ve->getVE()._indexX < _closeList[_ve->getVE()._xCount].idxX)
		{
			_ve->setVEState(1);
			_ve->setVEView(1);
			_ve->setVEX(_ve->getVE()._x + 1);
		}
		else if (_ve->getVE()._indexX > _closeList[_ve->getVE()._xCount].idxX)
		{
			_ve->setVEState(1);
			_ve->setVEView(0);
			_ve->setVEX(_ve->getVE()._x - 1);
		}
		else if (_ve->getVE()._indexY < _closeList[_ve->getVE()._yCount].idxY)
		{
			_ve->setVEState(1);
			_ve->setVEView(2);
			_ve->setVEY(_ve->getVE()._y + 1);
		}
		else if (_ve->getVE()._indexY > _closeList[_ve->getVE()._yCount].idxY)
		{
			_ve->setVEState(1);
			_ve->setVEView(3);
			_ve->setVEY(_ve->getVE()._y - 1);
		}

		if (_ve->getVE()._indexX == _closeList[_ve->getVE()._xCount].idxX &&
			_ve->getVE()._indexY == _closeList[_ve->getVE()._yCount].idxY)
		{
			_ve->setVCount(_ve->getVE()._xCount + 1, _ve->getVE()._yCount + 1);
		}


		// 에이스타 끝
		if (_closeList.size() >= 7)
		{
			if (_ve->getVE()._indexX == _closeList[6].idxX &&
				_ve->getVE()._indexY == _closeList[6].idxY)
			{
				for (int i = 0; i < _closeList.size(); i++)
				{
					_tile[_closeList[i].idxX][_closeList[i].idxY].unit = 0;
				}
				_ve->setVEastar(false);
				_ve->setVEIdx(_closeList[6].idxX, _closeList[6].idxY);
				_ve->setVCount(0, 0);
				_ve->setVEState(0);
				turn.set(0, 0);

				//카메라
				turn.set(1, 1);
				_cam.start = true;

			}
			
		}
		else
		{
			if (_ve->getVE()._indexX == _closeList.back().idxX &&
				_ve->getVE()._indexY == _closeList.back().idxY)
			{
				for (int i = 0; i < _closeList.size(); i++)
				{
					_tile[_closeList[i].idxX][_closeList[i].idxY].unit = 0;
				}
				_ve->setVEastar(false);
				_ve->setVEIdx(_closeList.back().idxX, _closeList.back().idxY);
				_ve->setVCount(0, 0);
				_ve->setVEState(0);
				turn.set(0, 0);
				
			}
		}
	}
	
	// 버몬트 인덱스변화
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			if (_ve->getVE()._x == _tile[i][j].x &&
				_ve->getVE()._y == _tile[i][j].y)
			{
				_ve->setVEIdx(i, j);
				_tile[i][j].unit = 1;
				break;
			}
		}
	}



	_ve->update();
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

	// 턴넘기기 , 카메라
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_cam.start = true;
	}

	// 카메라
	if (_cam.start)
	{
		// 버몬트 턴
		if (!turn[0] && !turn[1])
		{
			// 좌우
			if (_cam.x < _ve->getVE()._x)
			{
				_x -= CAMSPEED;
				_pl->setPX(_pl->getPL()._x - CAMSPEED);
				_ve->setVEX(_ve->getVE()._x - CAMSPEED);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x -= CAMSPEED;
					}
				}
			}
			else if (_cam.x > _ve->getVE()._x)
			{
				_x += CAMSPEED;
				_pl->setPX(_pl->getPL()._x + CAMSPEED);
				_ve->setVEX(_ve->getVE()._x + CAMSPEED);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].x += CAMSPEED;
					}
				}
			}

			// 상하
			if (_cam.y < _ve->getVE()._y)
			{
				_y -= CAMSPEED;
				_pl->setPY(_pl->getPL()._y - CAMSPEED);
				_ve->setVEY(_ve->getVE()._y - CAMSPEED);
				for (int j = 0; j < V_NUM; j++)
				{
					for (int i = 0; i < H_NUM; i++)
					{
						_tile[i][j].y -= CAMSPEED;
					}
				}
			}
			else if (_cam.y > _ve->getVE()._y)
			{
				_y += CAMSPEED;
				_pl->setPY(_pl->getPL()._y + CAMSPEED);
				_ve->setVEY(_ve->getVE()._y + CAMSPEED);
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
			RECT ve = RectMakeCenter(_ve->getVE()._x, _ve->getVE()._y, 30, 30);
			if (IntersectRect(&temp, &_cam.rc, &ve))
			{
				turn.set(0, 1);
				_cam.start = false;
			}
		}

		// 살라딘 턴
		if (turn[1])
		{
			// 좌우
			if (_cam.x < _pl->getPL()._x)
			{
				_x -= CAMSPEED;
				_pl->setPX(_pl->getPL()._x - CAMSPEED);
				_ve->setVEX(_ve->getVE()._x - CAMSPEED);
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
				_x += CAMSPEED;
				_pl->setPX(_pl->getPL()._x + CAMSPEED);
				_ve->setVEX(_ve->getVE()._x + CAMSPEED);
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
				_y -= CAMSPEED;
				_pl->setPY(_pl->getPL()._y - CAMSPEED);
				_ve->setVEY(_ve->getVE()._y - CAMSPEED);
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
				_y += CAMSPEED;
				_pl->setPY(_pl->getPL()._y + CAMSPEED);
				_ve->setVEY(_ve->getVE()._y + CAMSPEED);
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
				turn.set(1, 0);
				_cam.start = false;
			}
		}
	}

	// 버몬트 턴
	if (turn[0])
	{
		// 플레이어 근처가 아니면 a스타 발동
		if ((_ve->getVEIndexX() != _pl->getPL()._indexX - 2 || _ve->getVEIndexX() != _pl->getPL()._indexX + 2))
		{
			if (_tile[_pl->getPL()._indexX - 2][_pl->getPL()._indexY].unit == 0)
				Astar(_ve->getVE()._indexX, _ve->getVE()._indexY, _pl->getPL()._indexX - 2, _pl->getPL()._indexY);
			else
				Astar(_ve->getVE()._indexX, _ve->getVE()._indexY, _pl->getPL()._indexX + 2, _pl->getPL()._indexY);

			// 에이스타 시작
			if (_closeList.size() > 0)	_ve->setVEastar(true);
		}

		// 플레이어 양옆쪽이면 공격
		if ((_ve->getVEIndexX() == _pl->getPL()._indexX - 2 || _ve->getVEIndexX() == _pl->getPL()._indexX + 2) &&
			_ve->getVEIndexY() == _pl->getPL()._indexY)
		{
			_pl->setPState(4);
			_ve->setVEState(2);

			int sta = _pl->getPL()._indexX - _ve->getVEIndexX();

			switch (sta)
			{
			case 2:
				_ve->setVEView(1);
				_pl->setPView(0);
				break;

			case -2:
				_ve->setVEView(0);
				_pl->setPView(1);
				break;

			default:
				break;
			}
		}

		turn.set(0, 0); //1번만 발동되야하므로 바로 끔
	}

	if(_ui->getTigerState()) _ti->update(_pl,_ve);
	_ui->update();
}

void Battle::render(void)
{
    // 배경
   IMAGEMANAGER->findImage("전투맵")->render(getMemDC(),_x,_y);
   IMAGEMANAGER->findImage("MapInfo")->render(getMemDC(), 790, 5);
   FONTMANAGER->drawText(getMemDC(), 880, 20, 15, 255, 255, 255, "굴림", false, "형제여!");
   FONTMANAGER->drawText(getMemDC(), 950, 45, 15, 255, 255, 255, "굴림", true, "평  지");
   FONTMANAGER->drawInt(getMemDC(), 940, 85, 15, 255, 255, 255, "굴림", false, (char*)GOLD->getGold());
   FONTMANAGER->drawText(getMemDC(), 1000, 85, 15, 255, 255, 255, "굴림", false, "eld");

   DrawRectMake(getMemDC(), _cam.rc);

   // 턴을 표시하는 UI
   if (_ve->getVE()._state>=1)	// 버몬트턴
   {
	   _veTick++;
	   if (_veTick % 2 == 0)_veFrame++;
	   if (_veFrame > IMAGEMANAGER->findImage("적턴")->getMaxFrameX())_veFrame = 0;
	   IMAGEMANAGER->findImage("적턴")->frameRender(getMemDC(), _ve->getVE()._x + 17, _ve->getVE()._y - 70, _veFrame, 0);

   }
   else
   {
	   _veTick++;
	   if (_veTick % 2 == 0)_veFrame++;
	   if (_veFrame > IMAGEMANAGER->findImage("살라딘턴")->getMaxFrameX())_veFrame = 0;
	   IMAGEMANAGER->findImage("살라딘턴")->frameRender(getMemDC(),_pl->getPL()._x+17,_pl->getPL()._y-70, _veFrame, 0);
   }



   //// 임시 이동타일 보이기
   //if (_closeList.size() > 0)
   //{
	  // for (int i = 0; i < _closeList.size(); i++)
	  // {
		 //  DrawRectMake(getMemDC(), RectMake(_tile[_closeList[i].idxX][_closeList[i].idxY].x,
			//   _tile[_closeList[i].idxX][_closeList[i].idxY].y, 40, 32));

	  // }
   //}

#pragma region 마우스타일, 맵타일그리기
   // 마우스타일
   if (!_ui->getSkillState()&& _ui->getTileState())
   {
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

#pragma region skillUI

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
	#pragma region 스킬온

	   if (_ui->getSkillState())
	   {
		   if (_sk->getSkillXY().size() < 8)
		   {
			   _sk->setSkillXY(_tile[_ve->getVEIndexX()][_ve->getVEIndexY()].x-8, _tile[_ve->getVEIndexX()][_ve->getVEIndexY()].y-115, 12, true);
		   }

		   if (_sk->getBitset().any() == 0)
		   {
			_sk->setBitset(0, 1);
		   }
		   IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), 255);
		   if (_sk->getBitset()[0] == 1)
		   {
			   _pl->setPState(3);
			   _pl->setPSkill(0);
		   }
		   if (_sk->getBitset()[1] == 1)
		   {
			   _skillTick++;
			   if (_skillTick % 5 == 0)
			   {
				   _skillFrame++;
				   _pl->setPSkill(_skillFrame);
			   }
		   }
		   if (_sk->getBitset()[5] == 1)
		   {
			   _pl->setPState(0);
		   }
		   if (_sk->getBitset()[6] == 1)
		   {
			   _ui->setSkillState(false);
			   _ui->setUIState(false);
			   _ui->setAbilityState(false);
			   _sk->getBitset().reset();
		   }


		   // 카메라 쉐이킹
		   if (_sk->getBitset()[3] == 1 )
		   {
			   if (_skillTick % 2 == 0)
			   {
				   if (_skillBool == false) _skillBool = true;
				   else if (_skillBool == true) _skillBool = false;
			   }
			   if (_skillBool)
			   {
				   for (int j = 0; j < V_NUM; j++)
				   {
					   for (int i = 0; i < H_NUM; i++)
					   {
						   _tile[i][j].x -= 2;
						   _tile[i][j].y -= 2;
					   }
				   }

				   _x -= 2;
				   _y -= 2;
			   }
			   else
			   {
				   for (int j = 0; j < V_NUM; j++)
				   {
					   for (int i = 0; i < H_NUM; i++)
					   {
						   _tile[i][j].x += 2;
						   _tile[i][j].y += 2;
					   }
				   }

				   _x += 2;
				   _y += 2;
			   }
		   }
		   else
		   {
			   _pl->setPX(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].x);
			   _pl->setPY(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].y);
		   }
	   }

	  
	#pragma endregion


	#pragma region 스킬끝나면 게임종료
	   if (!_emRender)
	   {
		   if (_sk->getBitset()[6] == 1)
		   {
			   _skillTick = 0;
			   _emRender = true;
		   }
	   }

	#pragma endregion
	   
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
			int view = _pl->getPL()._indexX - _ve->getVEIndexX();
			switch (view)
			{
				// 우
			case 2:
				_pl->setPView(0);
				_ve->setVEView(1);
				_ve->setVEState(3);
				break;

				// 좌
			case -2:
				_pl->setPView(1);
				_ve->setVEView(0);
				_ve->setVEState(3);
				break;

			default:
				break;
			}
			_ui->setAtkTile(false);
		}

		
	}
	if(_ui->getSkillState()) _sk->UpSkill(_pl);
	if(_ui->getTigerState())IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), 255);
   _ve->render();
   _pl->render();
   _ui->render(_pl);
	if (_ui->getTigerState()) _ti->render(_pl,_ve);
	if (_ui->getSkillState())	_sk->DownSkill(_pl);
	if (_ti->getStep()[4]) _ui->setTigerState(false);

#pragma endregion



   // 시나리오 클리어
   if (_emRender)
   {
	   _skillTick++;
	   IMAGEMANAGER->findImage("시나리오클리어")->alphaRender(getMemDC(), 0, 300, 50);
	   IMAGEMANAGER->findImage("클리어광원")->alphaRender(getMemDC(), 0, 300, 150);
	   IMAGEMANAGER->findImage("클리어텍스트")->alphaRender(getMemDC(), 305, 325, 100);
	   IMAGEMANAGER->findImage("클리어텍스트광원")->alphaRender(getMemDC(), 300, 320, 255);
	   if (_skillTick > 200)
		   SCENEMANAGER->changScene("로딩","2번시나리오");
   }



}

void Battle::Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY)
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


