#pragma once
#include "GameNode.h"

#define ROUTE_L "Resources/Images/Loading/"

class Loading : public GameNode
{
private:
	// �ð� üũ�� ƽ
	int _tick;

	// �ε� ĳ���� �̹����� ���� ���� �� ����
	int _loadingImgRanNum;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Loading() {}
	~Loading() {}
};