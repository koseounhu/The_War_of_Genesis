#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(void) //float는 계산범위 넓어서 보통 inline화가 안 되긴 한다. 통일성을 위해 적어둠.
	{
		return (float)rand() / (float)RAND_MAX;
	}

	inline float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};