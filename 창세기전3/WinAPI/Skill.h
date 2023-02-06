#pragma once
#include "GameNode.h" 

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

struct SKILLXY
{
	float x;
	float y;
	int frame;
	bool start;
};

class Skill : public GameNode
{
private:
	// ½ºÅ³
	bitset<20>_skill;
	bitset<10>_skillSound;
	int _tick;
	int _circleFrame;
	bool _num2;

	vector<TEMP> _temp;
	vector<TEMP>_fire;
	vector<TEMP>_fireball;
	vector<particle> _particle;
	vector<SKILLXY> _enemyXY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void UpSkill(Player* _pl);
	void DownSkill(Player* _pl);

	bitset<20> getBitset() { return _skill; }
	void setBitset(int bitnum, bool state) { _skill.set(bitnum,state); }
	vector<SKILLXY> getSkillXY(void) { return _enemyXY; }
	void setSkillXY(float x, float y, int frame, bool start) { _enemyXY.push_back({ x,y,frame,start }); }
	void clearSkillXY(void) { _enemyXY.clear(); }

	Skill() {}
	~Skill() {}
};

