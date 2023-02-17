#include "Stdafx.h"
#include "Battle3.h"

void Battle3::moveTileStar(int startIdxX, int startIdxY)
{
    // �̵� �� �Ÿ� �� �ʱ�ȭ
    int moveCost = 0;

    // ��� ��ġ �ʱ�ȭ
    int _startIdxX;
    int _startIdxY;

    // ���� ���� ����
    int canMoveNum = 77;

    // ���� �� �Է�
    _startIdxX = startIdxX;
    _startIdxY = startIdxY;

    // Ÿ�� moveTile* üũ �ʱ�ȭ
    for (int j = 0; j < V_NUM; j++)
    {
        for (int i = 0; i < H_NUM; i++)
        {
            _tile[i][j].moveTileColli = false;
            _tile[i][j].moveTileColli = _tile[i][j].mapColli;
            //if (_tile[i][j].unit != 0) _tile[i][j].moveTileColli = true;
        }
    }

    // moveTile* ���� �ʱ�ȭ
    bool _moveTileBreak = false;

    // ��� ����
    _canMoveList.clear();
    _cantMoveList.clear();

    // �� �� �ִ� ��Ͽ� ���� �ڸ� �߰� �� �ݱ�
    _canMoveList.push_back({ _tile[startIdxX][startIdxY].idxX,
       _tile[startIdxX][startIdxY].idxY, 0 });
    _tile[startIdxX][startIdxY].moveTileColli = true;

    // �� �� �ִ� Ÿ�� �˰��� �ݺ�
    while (!_moveTileBreak)
    {
        // �� �� �ִ� ��Ͽ� ���� �߰�
        if (_startIdxX > 0 && moveCost < canMoveNum + 1)
        {
            if (!_tile[_startIdxX - 1][_startIdxY].moveTileColli)
            {
                if (_tile[_startIdxX - 1][_startIdxY].unit == 0)
                {
                    _canMoveList.push_back({ _startIdxX - 1, _startIdxY, moveCost });
                    _tile[_startIdxX - 1][_startIdxY].moveTileColli = true;
                }
            }
        }

        // �� �� �ִ� ��Ͽ� ���� �߰�
        if (_startIdxX < H_NUM - 1 && moveCost < canMoveNum + 1)
        {
            if (!_tile[_startIdxX + 1][_startIdxY].moveTileColli)
            {
                if (_tile[_startIdxX + 1][_startIdxY].unit == 0)
                {
                    _canMoveList.push_back({ _startIdxX + 1, _startIdxY, moveCost });
                    _tile[_startIdxX + 1][_startIdxY].moveTileColli = true;
                }
            }
        }

        // �� �� �ִ� ��Ͽ� ���� �߰�
        if (_startIdxY > 0 && moveCost < canMoveNum + 1)
        {
            if (!_tile[_startIdxX][_startIdxY - 1].moveTileColli)
            {
                if (_tile[_startIdxX][_startIdxY - 1].unit == 0)
                {
                    _canMoveList.push_back({ _startIdxX, _startIdxY - 1, moveCost });
                    _tile[_startIdxX][_startIdxY - 1].moveTileColli = true;
                }
            }
        }

        // �� �� �ִ� ��Ͽ� ���� �߰�
        if (_startIdxY < V_NUM - 1 && moveCost < canMoveNum + 1)
        {
            if (!_tile[_startIdxX][_startIdxY + 1].moveTileColli)
            {
                if (_tile[_startIdxX][_startIdxY + 1].unit == 0)
                {
                    _canMoveList.push_back({ _startIdxX, _startIdxY + 1, moveCost });
                    _tile[_startIdxX][_startIdxY + 1].moveTileColli = true;
                }
            }
        }

        // ���� ����
        if (moveCost == canMoveNum)
        {
            _moveTileBreak = true;
            moveCost = 0;
        }
        // �̵� �� �Ÿ� �� ������Ʈ

        // ���� �� ������Ʈ
        if (_canMoveList.size() != 0)
        {
            _startIdxX = _canMoveList[moveCost].idxX;
            _startIdxY = _canMoveList[moveCost].idxY;
            moveCost++;
        }
    }

    // �� �� ���� Ÿ�� �˰��� �ݺ�
    for (int i = 0; i < _canMoveList.size(); i++)
    {
        // �� �� ���� ��Ͽ� ���� �߰�
        if (_canMoveList[i].idxX > 0)
        {
            if (!_tile[_canMoveList[i].idxX - 1][_canMoveList[i].idxY].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX - 1, _canMoveList[i].idxY, moveCost });
                _tile[_canMoveList[i].idxX - 1][_canMoveList[i].idxY].moveTileColli = true;
            }
            if (!_tile[_canMoveList[i].idxX - 2][_canMoveList[i].idxY].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX - 2, _canMoveList[i].idxY, moveCost });
                _tile[_canMoveList[i].idxX - 2][_canMoveList[i].idxY].moveTileColli = true;
            }
        }

        // �� �� ���� ��Ͽ� ���� �߰�
        if (_canMoveList[i].idxX < H_NUM - 1)
        {
            if (!_tile[_canMoveList[i].idxX + 1][_canMoveList[i].idxY].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX + 1, _canMoveList[i].idxY, moveCost });
                _tile[_canMoveList[i].idxX + 1][_canMoveList[i].idxY].moveTileColli = true;
            }
            if (!_tile[_canMoveList[i].idxX + 2][_canMoveList[i].idxY].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX + 2, _canMoveList[i].idxY, moveCost });
                _tile[_canMoveList[i].idxX + 2][_canMoveList[i].idxY].moveTileColli = true;
            }
        }

        // �� �� ���� ��Ͽ� ���� �߰�
        if (_canMoveList[i].idxY > 0)
        {
            if (!_tile[_canMoveList[i].idxX][_canMoveList[i].idxY - 1].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX, _canMoveList[i].idxY - 1, moveCost });
                _tile[_canMoveList[i].idxX][_canMoveList[i].idxY - 1].moveTileColli = true;
            }
            if (!_tile[_canMoveList[i].idxX][_canMoveList[i].idxY - 2].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX, _canMoveList[i].idxY - 2, moveCost });
                _tile[_canMoveList[i].idxX][_canMoveList[i].idxY - 2].moveTileColli = true;
            }
        }

        // �� �� ���� ��Ͽ� ���� �߰�
        if (_canMoveList[i].idxY < V_NUM - 1)
        {
            if (!_tile[_canMoveList[i].idxX][_canMoveList[i].idxY + 1].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX, _canMoveList[i].idxY + 1, moveCost });
                _tile[_canMoveList[i].idxX][_canMoveList[i].idxY + 1].moveTileColli = true;
            }
            if (!_tile[_canMoveList[i].idxX][_canMoveList[i].idxY + 2].moveTileColli)
            {
                _cantMoveList.push_back({ _canMoveList[i].idxX, _canMoveList[i].idxY + 2, moveCost });
                _tile[_canMoveList[i].idxX][_canMoveList[i].idxY + 2].moveTileColli = true;
            }
        }

    }


}