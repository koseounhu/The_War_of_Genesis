#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Skill.h"
#include "Enemy.h"
#include "UI.h"
#include "Vermouth.h"
#include "Tiger.h"

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
struct OpenList
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* 닫힌 목록
struct CloseList
{
	int idxX;
	int idxY;
	float fromStartCost;
};

struct moveTile2
{
	int idxX;
	int idxY;
	int moveCost;
};

// 타일 그리기
struct TILE
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

struct CAMERA
{
	RECT rc;

	int x;
	int y;

	bool center;
	bool start;
};

class Battle : public GameNode
{
private:
	// 스킬
	int _skillTick;
	int _skillFrame;
	bool _skillBool;


	// 시작시 카메라 무빙
	bool _gameStart;

	// 타일을 만들기위한 구조체
	TILE _tile[H_NUM][V_NUM];
	

	// 열린 목록
	vector<OpenList> _openList;

	// 닫힌 목록
	vector<CloseList> _closeList;

	// 움직일 타일
	vector<moveTile2> _canMoveList;
	vector<moveTile2> _cantMoveList;

	// AStar 종료 체크
	bool _aStarBreak;

	// AStar 함수
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);

	// 이동가능타일
	void moveTileStar(int startIdxX, int startIdxY);

	// 플레이어
	Player* _pl;
	Vermouth* _ve;
	Skill* _sk;
	Tiger* _ti;
	bool _emRender;
	UI* _ui;
	int _mouseTileFrame;

	// 카메라
	CAMERA _cam;

	// 턴
	bitset<4> turn;
	
	// 배경 움직이기위한 위치값
	int _x, _y;

	// 버몬트 턴 프레임
	int _veFrame;
	int _veTick;
	
	// 마우스
	RECT _Mrc;
	int _frame;
	int _tick;

	//맵 좌표
	int _mapX;
	int _mapY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	Battle() {}
	~Battle() {}
};

