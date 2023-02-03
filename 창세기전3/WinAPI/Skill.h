#pragma once
#include "GameNode.h" 

class Enemy;
class Player;

struct TEMP
{
	int x;
	int y;
	int frame;
	bool start;
};
struct particle
{
	float x;
	float y;
	int frame;
	float speed;
	int alpha;
	bool start;
};

class Skill : public GameNode
{
private:
	// ½ºÅ³
	bitset<20>_skill;
	int _tick;

	vector<TEMP> _temp;
	vector<TEMP>_fire;
	vector<TEMP>_fireball;
	vector<particle> _particle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void skillRender(Player* _pl, Enemy* _em[10]);

	bitset<20> getBitset() { return _skill; }
	void setBitset(bitset<20>bit) { _skill = bit; }
	void skillUp(Player* _pl, Enemy* _em[10]);
	void skillDown(Player* _pl, Enemy* _em[10]);

	Skill() {}
	~Skill() {}
};

