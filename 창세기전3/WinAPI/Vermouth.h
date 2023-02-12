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
	int _atked;
	bool _atkSound;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VERMOUTH getVE(void) { return _ve; }

	int getVEIndexX(void) { return _ve._indexX; }
	int getVEIndexY(void) { return _ve._indexY; }

	void setVEX(int x) { _ve._x = x; }
	void setVEY(int y) { _ve._y = y; }
	void setVEState(int num) { _ve._state = num; }
	void setVEView(int num) { _ve._view = num; }
	void setVEIdx(int idxx, int idxy) {	_ve._indexX = idxx;
									_ve._indexY = idxy;}
	void setVCount(int numX, int numY) {_ve._xCount = numX;
										_ve._yCount = numY;}

	void setVEastar(bool state) { _ve._astar = state; }



	Vermouth() {}
	~Vermouth() {}
};

