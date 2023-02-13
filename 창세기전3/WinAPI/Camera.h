#pragma once
#include "GameNode.h"
class Camera : public GameNode
{
private:
	RECT camera;





public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Camera() {}
	~Camera() {}
};

