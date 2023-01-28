#pragma once
#include "GameNode.h"


class WorldMap : public GameNode
{
private:
	int _tick;
	int _loopX, _loopY;
	int _pointFrame;
	int _bgX, _bgY;

	RECT _point;

	RECT _button[4];
	int _buttonNum[4];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);






	WorldMap() {}
	~WorldMap() {}
};

