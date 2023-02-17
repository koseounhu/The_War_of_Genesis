#pragma once
#include "GameNode.h"


class Scenario : public GameNode
{
private:

	RECT _rc;
	int _tick;

	// 검은 화면
	int _alpha;

	// 다음시나리오 넘어가기전 불꽃
	int _fireAlpha;

	// 다음 시나리오
	bool _next;

	// 마우스
	RECT _Mrc;
	int _frame;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Scenario(){}
	~Scenario() {}
};

