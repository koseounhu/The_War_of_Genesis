#pragma once
#include "GameNode.h"


class Enemy : public GameNode
{
private:
	float _enemyX;
	float _enemyY;

	int _enemyIdxX;
	int _enemyIdxY;

	int _enemyFrame;
	int _tick;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float x, float y, int state);

	float getEnemyX(void) { return _enemyX; }
	float getEnemyY(void) { return _enemyY; }

	int getEnemyIdxX(void) { return _enemyIdxX; }
	int getEnemyIdxY(void) { return _enemyIdxY; }
	void setEnemyIdxX(int idxX) { _enemyIdxX = idxX; }
	void setEnemyIdxY(int idxY) { _enemyIdxY = idxY; }

	Enemy() {}
	~Enemy() {}
};

