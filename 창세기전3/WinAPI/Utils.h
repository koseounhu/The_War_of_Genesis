#pragma once

//디그리 1도의 라디안 값
#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
#define PI_2			6.283185308f


#define FLOAT_EPSILON	0.0001f

#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1,f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다.
	float getDistance(float startX, float startY, float endX, float endY);
	// start부터 end까지의 각을 라디안으로 구한다.
	float getAngle(float startX, float startY, float endX, float endY);

}