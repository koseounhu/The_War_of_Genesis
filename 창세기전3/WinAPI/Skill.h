#pragma once
#include "GameNode.h" 
struct TEMP
{
	int x;
	int y;

	bool start;

	int frame;
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

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bitset<20> getBitset() { return _skill; }
	void setBitset(int num, bool bitset) { _skill.set(num, bitset); }
	void SkillRender(int x, int y);


	Skill() {}
	~Skill() {}
};

