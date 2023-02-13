#pragma once
#include "GameNode.h"
#include "Enemy2.h"
#include "Player.h"
#include "UI.h"

#pragma region ��, A*

// ���� ĭ ����
#define H_NUM 50
// ���� ĭ ����
#define V_NUM 60
// �� ĭ�� ���� ����
#define WIDTH 40
// �� ĭ�� ���� ����
#define HEIGHT 32

// A* �� ��� �ӽ� �ʱⰪ
#define ASTAR_MAX_COST 9999999.9f

// A* ���� ���
struct OpenList3
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* ���� ���
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
// Ÿ�� �׸���
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

	//���
	BG _bg;
	
	// UI
	UI* _ui;

	// UNIT
	Player* _pl;
	Enemy2* _em;


#pragma region Astar

	// Ÿ���� ��������� ����ü
	TILE3 _tile[H_NUM][V_NUM];

	// ���� ���
	vector<OpenList3> _openList;

	// ���� ���
	vector<CloseList3> _closeList;

	// ������ Ÿ��
	vector<moveTile3> _canMoveList;
	vector<moveTile3> _cantMoveList;

	// AStar ���� üũ
	bool _aStarBreak;

	// AStar �Լ�
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

