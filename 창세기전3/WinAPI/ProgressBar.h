#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	GImage* _progressBarUp;
	GImage* _progressBarDown;

	RECT _rc;
	int _x, _y;

	float _width;


public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGaug(float currentScore, float maxScore);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }



	ProgressBar() {}
	virtual ~ProgressBar();
};

