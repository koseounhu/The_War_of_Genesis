#pragma once
#include "GameNode.h"


class WorldMap : public GameNode
{
private:

	int _tick;
	int _loopX, _loopY;
	int _pointFrame;
	int _bgX, _bgY;
	int _profileFrame;
	int _alpha;

	RECT _point;

	RECT _button[5];
	int _buttonNum[5];

	int _selectFrame;

	int _selectPoint;

	bool _ui;
	bool _move;
	bool _move2;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);






	WorldMap() {}
	~WorldMap() {}
};

