#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Skill.h"
#include "Enemy.h"


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
struct OpenList2
{
	int idxX;
	int idxY;
	float fromStartCost;
	float toEndCost;
	float totalCost;
};

// A* ���� ���
struct CloseList2
{
	int idxX;
	int idxY;
	float fromStartCost;
};

struct moveTile
{
	int idxX;
	int idxY;
	int moveCost;
};
// Ÿ�� �׸���
struct TILE2
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
class Battle2 : public GameNode
{
private:

	// ������ Ÿ�� ����
	bool _groundTile;

	// ui
	bool _ui;
	bool _ability;
	bool _tileOn;
	bool _skillOn;

	// ��ų
	int _skillTick;
	int _skillFrame;
	bool _skillBool;


	// ���۽� ī�޶� ����
	bool _gameStart;

	// Ÿ���� ��������� ����ü
	TILE2 _tile[H_NUM][V_NUM];

	// ���� ���
	vector<OpenList2> _openList;

	// ���� ���
	vector<CloseList2> _closeList;

	// ������ Ÿ��
	vector<moveTile> _canMoveList;
	vector<moveTile> _cantMoveList;

	// AStar ���� üũ
	bool _aStarBreak;

	// AStar �Լ�
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);

	// �÷��̾�
	Player* _pl;
	Enemy* _em[10];
	Skill* _sk;
	bool _emRender;
	
	// ȭ�鳡���� �浹�� ��� �����̱� ���� ��Ʈ
	RECT _rc[4];

	// ��� �����̱����� ��ġ��
	int _x, _y;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void moveTileStar(int startIdxX, int startIdxY);
	TILE2 getTile(void) { return _tile[H_NUM][V_NUM]; }

	Battle2() {}
	~Battle2() {}
};

