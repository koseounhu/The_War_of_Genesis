#pragma once
#include "GameNode.h"
struct VERMOUTH
{

	int _x, _y;
	int _indexX, _indexY;
	int _xCount, _yCount;


	int _state;
	int _view;

	bool _astar;

	int skill;
	int frame;
	int tick;
};

class Vermouth:public GameNode
{
private:
	VERMOUTH _ve;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setVEX(int x) { _ve._x = x; }
	void setVEY(int y) { _ve._y = y; }

	VERMOUTH getVE(void) { return _ve; }

	Vermouth() {}
	~Vermouth() {}
};

