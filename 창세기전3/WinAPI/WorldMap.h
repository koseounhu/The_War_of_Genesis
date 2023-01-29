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

	RECT _button[4];
	int _buttonNum[4];

	int _selectFrame;

	bool _ui;
	bool _move;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);






	WorldMap() {}
	~WorldMap() {}
};

