#pragma once
#include "GameNode.h"

class Player;
class Vermouth;


struct TIGER
{
	float x;
	float y;
	int alpha;
	int frame;
};

struct LIGHT
{
	int alpha;
	int frame;
};

struct DASH
{
	float x;
	float y;
	float speed;

	int alpha;
	int frame;
	int effectFrame;
};

struct SHADOW
{
	float x;
	float y;
	float speed;

	int alpha;

	bool start;
};

class Tiger : public GameNode
{
private:
	TIGER _ti;
	LIGHT _light;
	DASH _dash[4];
	SHADOW _shadow[40];

	int _circleFrame;

	bitset<5> _step;


	int _tick;

	bool _atkSound;


public:
	HRESULT init(void);
	void release(void);
	void update(Player* _pl, Vermouth* _ve);
	void render(Player* _pl, Vermouth* _ve);

	bitset<5> getStep(void) { return _step; }

	Tiger() {}
	~Tiger() {}
};

