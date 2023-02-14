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
	bool isAtk;

	int atkFrame;
	int walkFrame;
	int idleFrame;

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

	ENEMY2 getEm(void) { return _em; }


	void setX(int x) { _em.x = x; }
	void setY(int y) { _em.y = y; }

	void setIdx(int idxX, int idxY) { _em.indexX = idxX; _em.indexY = idxY; }

	void setCount(int countx, int county) { _em.xCount = countx; _em.yCount = county; }

	void setAstar(bool astar) { _em.astar = astar; }
	void setIsAtk(bool atk) { _em.isAtk = atk; }

	void setView(int view) { _em.view = view; }
	void setState(int state) { _em.state = state; }



	Enemy2() {}
	~Enemy2() {}
};

