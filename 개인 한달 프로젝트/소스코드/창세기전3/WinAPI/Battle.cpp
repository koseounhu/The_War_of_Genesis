#include "Stdafx.h"
#include "Battle.h"

HRESULT Battle::init(void)
{
#pragma region ȭ�� �浹��Ʈ
    _rc[0] = RectMake(0, 0, WINSIZE_X, 50);
    _rc[1] = RectMake(0, 0, 50, WINSIZE_Y);
    _rc[2] = RectMake(0,WINSIZE_Y-50, WINSIZE_X,50);
    _rc[3] = RectMake(WINSIZE_X-50,0, 50,WINSIZE_Y);
    _x = _y = 0;
#pragma endregion

#pragma region ��, A*
	// Ÿ�� �迭 �ʱ�ȭ
	for (int j = 0; j < V_NUM; j++)
	{
		for (int i = 0; i < H_NUM; i++)
		{
			_tile[i][j] = { i * WIDTH, j * HEIGHT, i, j, false, false, 0 };
		}
	}
#pragma endregion

	// �ӽ�
	_frame = 0;
	_count = 0;


    return S_OK;
}

void Battle::release(void)
{
}

void Battle::update(void)
{
#pragma region ���۽� ī�޶� ����
	if (!_gameStart)
	{
		if (_x > -250)
		{
			_x -= 3;

			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x -= 3;
				}
			}
		}
		else if (_x < -250 && _y > -1030)
		{
			_y -= 3;
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

    if (PtInRect(&_rc[3], _ptMouse))
    {
        if (_x > -570)
        {
            _x -= 2;

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
			for (int j = 0; j < V_NUM; j++)
			{
				for (int i = 0; i < H_NUM; i++)
				{
					_tile[i][j].x += 2;
				}
			}
        }
    }
    else if(PtInRect(&_rc[2],_ptMouse))
    {
        if (_y > -1030)
        {
            _y -= 2;
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

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int j = 0; j < V_NUM; j++)
		{
			for (int i = 0; i < H_NUM; i++)
			{
				// Ŭ���� ���� A* Ȱ��ȭ
				if (_ptMouse.x > _tile[i][j].x && _ptMouse.x < _tile[i + 1][j].x &&
					_ptMouse.y > _tile[i][j].y && _ptMouse.y < _tile[i][j + 1].y)
				{
					Astar(10, 10, i, j);
				}
			}
		}
	}



}

void Battle::render(void)
{
    // ���
   IMAGEMANAGER->findImage("������")->render(getMemDC(),_x,_y);
   
   // �� ��ȹ���� �� �׸���
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


   // A* ���� ��� ��Ʈ�� �׸���
   if (_closeList.size() != 0)
	   for (int i = 0; i < _closeList.size(); i++)
	   {
		   DrawRectMake(getMemDC(),
			   RectMake(_tile[_closeList[i].idxX][_closeList[i].idxY].x,
				   _tile[_closeList[i].idxX][_closeList[i].idxY].y,
				   WIDTH, HEIGHT));
	   }



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


