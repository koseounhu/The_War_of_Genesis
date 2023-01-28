#pragma once
#include "GameNode.h"

class Openning : public GameNode
{
private:
	// 선택창
	RECT _rc[5];


	// 배경
	int _BGalpha;
	int _count;

	// 불꽃
	int _fireAlpha;
	int _fireFame;
	bool _fire;

	// 넘어가는 화면
	bool _next;
	int _nextAlpha;

	// 가운데 글씨 프레임
	int _textFrame;

	bitset<8>_textImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	Openning() {}
	~Openning() {}
};

