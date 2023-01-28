#pragma once
#include "GameNode.h"


#pragma region ��, A*

// ���� ĭ ����
#define H_NUM 40
// ���� ĭ ����
#define V_NUM 50
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
};
#pragma endregion


class Battle : public GameNode
{
private:
	// �ӽ� ������
	int _count;
	int _frame;
	
	// ���۽� ī�޶� ����
	bool _gameStart;

	// Ÿ���� ��������� ����ü
	TILE _tile[H_NUM][V_NUM];

	// ���� ���
	vector<OpenList> _openList;

	// ���� ���
	vector<CloseList> _closeList;

	// AStar ���� üũ
	bool _aStarBreak;

	// AStar �Լ�
	void Astar(int startIdxX, int startIdxY, int endIdxX, int endIdxY);




	// ȭ�鳡���� �浹�� ��� �����̱� ���� ��Ʈ
	RECT _rc[4];
	
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

