#pragma once
#include "GameNode.h"
#include "Player.h"



#pragma region 맵, A*

// 가로 칸 개수
#define H_NUM 50
// 세로 칸 개수
#define V_NUM 60
// 한 칸의 가로 길이
#define WIDTH 40
// 한 칸의 세로 길이
#define HEIGHT 32

// A* 총 비용 임시 초기값
#define ASTAR_MAX_COST 9999999.9f

// A* 열린 목록
struct OpenList2
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* 닫힌 목록
struct CloseList2
{
	int idxX;
	int idxY;
	float fromStartCost;
};
// 타일 그리기
struct TILE2
{
	int x;
	int y;
	int idxX;
	int idxY;
	bool mapColli;
	bool aStarColli;
	int unit;
};
#pragma endregion
class Battle2 : public GameNode
{
private:
	// 시작시 카메라 무빙
	bool _gameStart;

	// 타일을 만들기위한 구조체
	TILE2 _tile[H_NUM][V_NUM];

	// 열린 목록
	vector<OpenList2> _openList;

	// 닫힌 목록
	vector<CloseList2> _closeList;

	// AStar 종료 체크
	bool _aStarBreak;

	// AStar 함수
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);

	// 임시 플레이어
	Player* _pl;



	// 화면끝에서 충돌시 배경 움직이기 위한 렉트
	RECT _rc[4];

	// 배경 움직이기위한 위치값
	int _x, _y;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	Battle2() {}
	~Battle2() {}
};

