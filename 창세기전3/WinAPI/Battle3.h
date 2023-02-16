#pragma once
#include "GameNode.h"
#include "Enemy2.h"
#include "Player.h"
#include "UI.h"
#include "Dragon.h"

#pragma region ��, A*

// ���� ĭ ����
#define H_NUM 50
// ���� ĭ ����
#define V_NUM 40
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

struct RenOrder
{
	int numY;
	int numX;
};

struct OBJ
{
	int idxY;
	int idxX;
};

struct BG
{
	int x;
	int y;
};

struct CAM
{
	RECT rc;

	int x;
	int y;

	bitset<11> center;
	bool start;
};

class Battle3 : public GameNode
{
private:
	// ��üƽ
	int _tick;

	//���
	BG _bg;
	bool _gameStart;
	
	// UI
	UI* _ui;
	int _mouseTileFrame;

	// UNIT
	Player* _pl;
	Enemy2* _em[10];
	Dragon* _da;

	// TURN
	bitset<20> _turn;
	int _turnFrame;

	// CAM
	CAM _cam;

	// Object
	vector<OBJ> _obj;

	// ������ ����
	vector<pair<int,int>> _renOrder;

	// ���汤��ź ���Ϳ� �������ŭ ����1ȸ �ֱ����� ����
	bool _dragon;
	// ���汤��ź ī�޶� ����ŷ
	bool _shaking;

	int _end;

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
	
	// �̵�����Ÿ��
	void moveTileStar(int startIdxX, int startIdxY);

#pragma endregion

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renerOrder(void);


	Battle3() {}
	~Battle3() {}
};

