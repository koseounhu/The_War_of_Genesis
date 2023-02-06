#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Skill.h"
#include "Enemy.h"
#include "UI.h"
#include "Vermouth.h"

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
struct OpenList
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* ���� ���
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

// Ÿ�� �׸���
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


class Battle : public GameNode
{
private:


	// ��ų
	int _skillTick;
	int _skillFrame;
	bool _skillBool;


	// ���۽� ī�޶� ����
	bool _gameStart;

	// Ÿ���� ��������� ����ü
	TILE _tile[H_NUM][V_NUM];
	

	// ���� ���
	vector<OpenList> _openList;

	// ���� ���
	vector<CloseList> _closeList;

	// ������ Ÿ��
	vector<moveTile2> _canMoveList;
	vector<moveTile2> _cantMoveList;

	// AStar ���� üũ
	bool _aStarBreak;

	// AStar �Լ�
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);

	// �ٴ�Ÿ��
	void moveTileStar(int startIdxX, int startIdxY);

	// �÷��̾�
	Player* _pl;
	Vermouth* _ve;
	Skill* _sk;
	bool _emRender;
	UI* _ui;
	
	// ��
	bitset<4> turn;
	
	// ��� �����̱����� ��ġ��
	int _x, _y;


	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Battle() {}
	~Battle() {}
};

