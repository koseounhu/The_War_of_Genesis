#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다.
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	// start부터 end까지의 각을 라디안으로 구한다.
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0) angle = PI_2 - angle;
		
		return angle;

	}

}