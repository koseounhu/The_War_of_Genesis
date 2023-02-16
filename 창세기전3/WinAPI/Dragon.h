#pragma once
#include "GameNode.h"

class Player;
class Enemy2;

struct EmXY
{
	int x;
	int y;

	bool start;
};

struct PXY
{
	int x;
	int y;

	bool start;
};


class Dragon : public GameNode
{
private:
	vector<EmXY> _em;
	PXY _pl;

	int _tick;
	int _phase;
	int _frame;

	float _endSound;

	vector<int> _moveDragon;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// ��ų ����ϱ��� ���� �־��ְ� ����ؾ��� !!

	vector<EmXY> getEmXY(void) { return _em; }

	// �÷��̾�
	PXY getPl(void) { return _pl; }
	void setPl(int x, int y, int start) { _pl.x = x, _pl.y = y, _pl.start = start; }

	// ��
	vector<EmXY> getEm(void) { return _em; }
	void pushEM(int x, int y, bool start) { _em.push_back({ x,y,start }); }
	void setEm(int num, int x, int y, bool start) { _em[num].x = x, _em[num].y = y, _em[num].start = start; }

	// ������
	int getPhase(void) { return _phase; }


	Dragon() {}
	~Dragon() {}
};

