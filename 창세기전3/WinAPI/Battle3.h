#pragma once
#include "GameNode.h"
#include "Enemy2.h"
#include "Player.h"
#include "UI.h"

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
struct OpenList3
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* 닫힌 목록
struct CloseList3
{
	int idxX;
	int idxY;
	float fromStartCost;
};

struct moveTile3
{
	int idxX;
	int idxY;
	int moveCost;
};
// 타일 그리기
struct TILE3
{
	int x;
	int y;
	int idxX;
	int idxY;
	bool mapColli;
	bool aStarColli;
	int unit;
	bool moveTileColli;
};


#pragma endregion

struct BG
{
	int x;
	int y;
};

class Battle3 : public GameNode
{
private:

	//배경
	BG _bg;
	
	// UI
	UI* _ui;

	// UNIT
	Player* _pl;
	Enemy2* _em;


#pragma region Astar

	// 타일을 만들기위한 구조체
	TILE3 _tile[H_NUM][V_NUM];

	// 열린 목록
	vector<OpenList3> _openList;

	// 닫힌 목록
	vector<CloseList3> _closeList;

	// 움직일 타일
	vector<moveTile3> _canMoveList;
	vector<moveTile3> _cantMoveList;

	// AStar 종료 체크
	bool _aStarBreak;

	// AStar 함수
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);

#pragma endregion

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void moveTileStar(int startIdxX, int startIdxY);



	Battle3() {}
	~Battle3() {}
};

