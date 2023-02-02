#pragma once
#include "GameNode.h" 

class Enemy;
class Player;

struct TEMP
{
	int x;
	int y;

	bool start;

	int frame;
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
	int _skillFrame;
	int _effect;
	int _tick;

	vector<TEMP> _temp;
	vector<int>_frame;
	vector<particle> _particle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bitset<20> getBitset() { return _skill; }
	void setBitset(int num, bool bitset) { _skill.set(num, bitset); }
	void SkillRender(Player* _pl, Enemy* _em[10]);


	Skill() {}
	~Skill() {}
};

