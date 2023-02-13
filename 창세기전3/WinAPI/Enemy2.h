#pragma once
#include "GameNode.h"

struct ENEMY2
{
	int x;
	int y;

	int indexX;
	int indexY;

	int xCount;
	int yCount;

	bool astar;

	int frame;

	int view;
	int state;


};

class Enemy2 : public GameNode
{
private:
	int _tick;

	ENEMY2 _em;



public:	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Enemy2() {}
	~Enemy2() {}
};

