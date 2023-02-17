#include "Stdafx.h"
#include "Battle3.h"

void Battle3::moveTileStar(int startIdxX, int startIdxY)
{
    // 이동 시 거리 값 초기화
    int moveCost = 0;

    // 출발 위치 초기화
    int _startIdxX;
    int _startIdxY;

    // 종료 조건 숫자
    int canMoveNum = 77;

    // 시작 값 입력
    _startIdxX = startIdxX;
    _startIdxY = startIdxY;

    // 타일 moveTile* 체크 초기화
    for (int j = 0; j < V_NUM; j++)
    {
        for (int i = 0; i < H_NUM; i++)
        {
            _tile[i][j].moveTileColli = false;
            _tile[i][j].moveTileColli = _tile[i][j].mapColli;
            //if (_tile[i][j].unit != 0) _tile[i][j].moveTileColli = true;
        }
    }

    // moveTile* 종료 초기화
    bool _moveTileBreak = false;

    // 목록 삭제
    _canMoveList.clear();
    _cantMoveList.clear();

    // 갈 수 있는 목록에 시작 자리 추가 및 닫기
    _canMoveList.push_back({ _tile[startIdxX][startIdxY].idxX,
       _tile[startIdxX][startIdxY].idxY, 0 });
    _tile[startIdxX][startIdxY].moveTileColli = true;

    // 갈 수 있는 타일 알고리즘 반복
    while (!_moveTileBreak)
    {
        // 갈 수 있는 목록에 좌측 추가
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

        // 갈 수 있는 목록에 우측 추가
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

        // 갈 수 있는 목록에 상측 추가
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

        // 갈 수 있는 목록에 하측 추가
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

        // 종료 조건
        if (moveCost == canMoveNum)
        {
            _moveTileBreak = true;
            moveCost = 0;
        }
        // 이동 시 거리 값 업데이트

        // 시작 값 업데이트
        if (_canMoveList.size() != 0)
        {
            _startIdxX = _canMoveList[moveCost].idxX;
            _startIdxY = _canMoveList[moveCost].idxY;
            moveCost++;
        }
    }

    // 갈 수 없는 타일 알고리즘 반복
    for (int i = 0; i < _canMoveList.size(); i++)
    {
        // 갈 수 없는 목록에 좌측 추가
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

        // 갈 수 없는 목록에 우측 추가
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

        // 갈 수 없는 목록에 상측 추가
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

        // 갈 수 없는 목록에 하측 추가
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