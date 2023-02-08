#pragma once
#include "GameNode.h"

#define ROUTE_L "Resources/Images/Loading/"

class Loading : public GameNode
{
private:
	// 시간 체크용 틱
	int _tick;

	// 로딩 캐릭터 이미지용 임의 숫자 및 알파
	int _loadingImgRanNum;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Loading() {}
	~Loading() {}
};