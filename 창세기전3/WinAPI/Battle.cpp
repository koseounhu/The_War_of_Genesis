#include "Stdafx.h"
#include "Battle.h"


HRESULT Battle::init(void)
{
#pragma region 
   
#pragma endregion

	_x = _y = 0;

#pragma region ��, A*
	// Ÿ�� �迭 �ʱ�ȭ
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			_tile[i][j] = { i * WIDTH, j * HEIGHT, i, j, false, false, 0 };
		}
	}

	// ��� �ȼ� �̹����� ���� Ÿ�� �� �浹 ���� �ʱ�ȭ
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("������")->getMemDC(),
				_tile[i][j].x+100, _tile[i][j].y-40);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) _tile[i][j].unit = 2;
		}
	}
#pragma endregion

	// �÷��̾�
	_pl = new Player;
	_pl->init();
	_pl->setPX(_tile[23][25].x);
	_pl->setPY(_tile[23][25].y);
	_pl->setPcount(0, 0);

	_sk = new Skill;
	_sk->init();

	_ui = new UI;
	_ui->init();


    return S_OK;
}

void Battle::release(void)
{
	SAFE_DELETE(_sk);
	SAFE_DELETE(_pl);
	SAFE_DELETE(_ui);
}

void Battle::update(void)
{
#pragma region ���۽� ī�޶� ����
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
		else if (_x < -250 && _y > -500)
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
#pragma region ȭ�� ������ ����

	if (!_ui->getUIState())
	{

		if (_ptMouse.x > WINSIZE_X - 50)
		{
			if (_x > -570)
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
		else if (_ptMouse.y < 50)
		{
			if (_y < 0)
			{
				_y += 2;
				_pl->setPY(_pl->getPL()._y + 2);

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
#pragma region �÷��̾�
	// ���̽�Ÿ�� ���� �÷��̾� ������
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

	// �÷��̾� �ε�����ȭ
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

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		if (!_ui->getTotalUI())
		{
			// �÷��̾� ��Ʈ
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



	_ui->update();
}

void Battle::render(void)
{
    // ���
   IMAGEMANAGER->findImage("������")->render(getMemDC(),_x,_y);
   
#pragma region ���콺Ÿ��, ��Ÿ�ϱ׸���
   // ���콺Ÿ��
   if (!_ui->getSkillState())
   {
	   for (int j = 0; j < H_NUM; j++)
	   {
		   for (int i = 0; i < V_NUM; i++)
		   {
			   if (_tile[j][i].x < _ptMouse.x && _tile[j][i].y < _ptMouse.y &&
				   _tile[j + 1][i].x > _ptMouse.x && _tile[j][i + 1].y > _ptMouse.y)
			   {
				   IMAGEMANAGER->findImage("���콺Ÿ��")->alphaFrameRender(getMemDC(),
					   _tile[j][i].x, _tile[j][i].y, 150, 0, 0);
			   }

		   }
	   }
   }
   // �� ��ȹ���� �� �׸���
   if (KEYMANAGER->isToggleKey(VK_F10))
   {
	   for (int j = 0; j < V_NUM; j++)
	   {
		   for (int i = 0; i < H_NUM; i++)
		   {
			   // �»� -> ���
			   LineMake(getMemDC(), _tile[i][j].x, _tile[i][j].y,
				   _tile[i][j].x + WIDTH, _tile[i][j].y);
			   // �»� -> ����
			   LineMake(getMemDC(), _tile[i][j].x, _tile[i][j].y,
				   _tile[i][j].x, _tile[i][j].y + HEIGHT);
			   // ���� -> ���
			   LineMake(getMemDC(), _tile[i][j].x + WIDTH, _tile[i][j].y + HEIGHT,
				   _tile[i][j].x + WIDTH, _tile[i][j].y);
			   // ���� -> ����
			   LineMake(getMemDC(), _tile[i][j].x + WIDTH, _tile[i][j].y + HEIGHT,
				   _tile[i][j].x, _tile[i][j].y + HEIGHT);

				  

		   }
	   }
   }
#pragma endregion

#pragma region skillUI

#pragma region Ÿ�Ͽ�

   if (_ui->getTileState())
   {
	   moveTileStar(_pl->getPL()._indexX, _pl->getPL()._indexY);
	   for (int i = 0; i < V_NUM; i++)
	   {
		   for (int j = 0; j < H_NUM; j++)
		   {
			   if (_tile[j][i].moveTileColli)
			   {
				   IMAGEMANAGER->findImage("���Ÿ��")->alphaRender(getMemDC(), _tile[j][i].x, _tile[j][i].y, 100);
			   }
		   }
	   }
	   for (int i = 0; i < _cantMoveList.size(); i++)
	   {
		   IMAGEMANAGER->findImage("���Ÿ��")->alphaRender(getMemDC(), _tile[_cantMoveList[i].idxX][_cantMoveList[i].idxY].x,
			   _tile[_cantMoveList[i].idxX][_cantMoveList[i].idxY].y, 100);
	   }

	   if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	   {
		   // �÷��̾��̵�
		   if (_ui->getTileState())
		   {
			   for (int j = 0; j < V_NUM; j++)
			   {
				   for (int i = 0; i < H_NUM; i++)
				   {
					   // Ŭ���� ���� A* Ȱ��ȭ
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
#pragma region ��ų��
   if (_ui->getSkillState())
   {
	   bitset<20> bit;
	   bit.set(0, 1);
	   _sk->setBitset(bit);

	   IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), 150);
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


	   // ī�޶� ����ŷ
	   _skillTick++;
	   if (_sk->getBitset()[3] == 1 || _sk->getBitset()[5] == 1)
	   {
		   if (_skillTick % 3 == 0)
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
					   _tile[i][j].x -= 10;
				   }
			   }

			   for (int j = 0; j < V_NUM; j++)
			   {
				   for (int i = 0; i < H_NUM; i++)
				   {
					   _tile[i][j].y -= 10;
				   }
			   }
			   _x -= 10;
			   _y -= 10;
		   }
		   else
		   {
			   for (int j = 0; j < V_NUM; j++)
			   {
				   for (int i = 0; i < H_NUM; i++)
				   {
					   _tile[i][j].x += 10;
				   }
			   }

			   for (int j = 0; j < V_NUM; j++)
			   {
				   for (int i = 0; i < H_NUM; i++)
				   {
					   _tile[i][j].y += 10;
				   }
			   }
			   _x += 10;
			   _y += 10;
		   }
	   }
	   else
	   {
		   _pl->setPX(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].x);
		   _pl->setPY(_tile[_pl->getPL()._indexX][_pl->getPL()._indexY].y);
	   }
   }
#pragma endregion

   _sk->skillDown(_pl, _em);

#pragma region �� ����
   if (!_emRender)
   {
	   if (_sk->getBitset()[6] == 1)
	   {
		   _skillTick = 0;
		   _emRender = true;
	   }
   }

#pragma endregion
   _sk->render();
   _pl->render();
   _ui->render(_pl);
   _sk->skillUp(_pl, _em);

#pragma endregion


   // �ó����� Ŭ����
   //if (_emRender)
   //{
	  // _skillTick++;
	  // IMAGEMANAGER->findImage("�ó�����Ŭ����")->alphaRender(getMemDC(), 0, 300, 50);
	  // IMAGEMANAGER->findImage("Ŭ�����")->alphaRender(getMemDC(), 0, 300, 150);
	  // IMAGEMANAGER->findImage("Ŭ�����ؽ�Ʈ")->alphaRender(getMemDC(), 305, 325, 100);
	  // IMAGEMANAGER->findImage("Ŭ�����ؽ�Ʈ����")->alphaRender(getMemDC(), 300, 320, 255);
	  // if (_skillTick > 200)
		 //  SCENEMANAGER->changScene("�����");
   //}



}

void Battle::Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY)
{
	// �̵� �� �Ÿ� �� �ʱ�ȭ
	float moveCost = 1.0f;

	// ��� ��ġ �ʱ�ȭ
	int _startIdxX;
	int _startIdxY;

	// Ÿ�� A* üũ �ʱ�ȭ
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

	// AStar ���� �ʱ�ȭ
	_aStarBreak = false;

	// ���� ��� ����
	_closeList.clear();

	// ���� �� �Է�
	_startIdxX = startIdxX;
	_startIdxY = startIdxY;

	// �˰��� �ݺ�
	while (!_aStarBreak)
	{

		// ���� ��Ͽ� ���� �ڸ� �߰� �� �ݱ�
		_closeList.push_back({ _tile[_startIdxX][_startIdxY].idxX,
			_tile[_startIdxX][_startIdxY].idxY, 0.0f });
		_tile[_startIdxX][_startIdxY].aStarColli = true;

		// ���� ��� ����
		_openList.clear();

		// ���� ��Ͽ� ���� �߰�
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

		// ���� ��Ͽ� ���� �߰�
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

		// ���� ��Ͽ� ���� �߰�
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

		// ���� ��Ͽ� ���� �߰�
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

		// ���� ��� �� ��� ������Ʈ
		for (int i = 0; i < _openList.size(); i++)
		{
			_openList[i].totalCost = _openList[i].fromStartCost + _openList[i].toEndCost;
		}

		// ���� ����
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


		// �� ����� ���� ���� �ε��� �� ���
		int minCostIdx = 0;
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_openList[i].totalCost < _openList[minCostIdx].totalCost)
				minCostIdx = i;
		}

		// �� ����� ���� ���� ���� ���� ��Ͽ� �߰�
		if (_openList.size() != 0)
		{
			if (_openList[minCostIdx].idxX != _closeList[_closeList.size() - 1].idxX &&
				_openList[minCostIdx].idxY != _closeList[_closeList.size() - 1].idxY)
			{
				_closeList.push_back({ _openList[minCostIdx].idxX, _openList[minCostIdx].idxY,
					_openList[minCostIdx].fromStartCost + 1 });
			}
		}

		// �̵� �� �Ÿ� �� ������Ʈ
		moveCost++;

		// ���� �� ������Ʈ
		if (_openList.size() != 0)
		{
			_startIdxX = _openList[minCostIdx].idxX;
			_startIdxY = _openList[minCostIdx].idxY;
		}
	}
}


