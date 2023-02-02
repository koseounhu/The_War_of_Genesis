#pragma once
#include "GameNode.h"


class Enemy : public GameNode
{
private:
	float _enemyX;
	float _enemyY;
	int _enemyFrame;
	int _tick;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float x, float y, int state);

	float getEnemyX(void) { return _enemyX; }
	float getEnemyY(void) { return _enemyY; }

	Enemy() {}
	~Enemy() {}
};

