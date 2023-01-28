#pragma once
#include "GameNode.h"


class WorldMap : public GameNode
{
private:
	int _tick;
	int _loopX, _loopY;

	int _bgX, _bgY;





public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);






	WorldMap() {}
	~WorldMap() {}
};

