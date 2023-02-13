#include "Stdafx.h"
#include "Battle3.h"


HRESULT Battle3::init(void)
{
	// ���
	_bg.x = _bg.y = 0;

	// UI
	_ui = new UI;
	_ui->init();

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
				_tile[i][j].x + 100, _tile[i][j].y - 40);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) _tile[i][j].unit = 2;
		}
	}
#pragma endregion

#pragma region UNIT

	_pl = new Player;
	_pl->init();
	_pl->setPX(_tile[5][5].x);
	_pl->setPY(_tile[5][5].y);
	_pl->setPView(3);
	_pl->setPcount(0, 0);



	_em = new Enemy2;
	_em->init();


#pragma endregion

	return S_OK;
}

void Battle3::release(void)
{
	SAFE_DELETE(_em);
	SAFE_DELETE(_pl);
	SAFE_DELETE(_ui);
}

void Battle3::update(void)
{
	_pl->update();
	_em->update();
	_ui->update();
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
	if (_pl->getPL()._astar)
	{
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
	}
#pragma endregion

	// Astar ������
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("��ư", 1.0f);
		_pl->setPAstar(true);

		// �÷��̾��̵�
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


}

void Battle3::render(void)
{
	// ���
	IMAGEMANAGER->findImage("������3")->render(getMemDC(),_bg.x,_bg.y);

	// UNIT
	_pl->render();
	_em->render();

	// ȹ�׸���
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

	_ui->render(_pl);
}


void Battle3::Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY)
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