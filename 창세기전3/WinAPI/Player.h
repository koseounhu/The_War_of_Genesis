#pragma once
#include "GameNode.h"

struct PL
{

	int _x, _y;
	int _indexX, _indexY;
	int _xCount, _yCount;


	int _state;
	int _view;

	bool _astar;

	int skill;
};
class Player : public GameNode
{
private:
	int _tick;
	int _frame;
	PL _pl;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PL getPL(void) { return _pl; }

	void setPX(int x) { _pl._x = x; }
	void setPY(int y) { _pl._y = y; }
	void setPState(int num) { _pl._state = num; }
	void setPView(int num) { _pl._view = num; }
	void setPIndex(int numX, int numY) {_pl._indexX = numX;
										_pl._indexY = numY;}
	void setPAstar(bool astar) { _pl._astar = astar; }
	void setPcount(int numX, int numY) {_pl._xCount = numX;
										_pl._yCount = numY;}
	void setPSkill(int skillframe) { _pl.skill = skillframe; }

	Player() {}
	~Player() {}
};

