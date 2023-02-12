#pragma once

//��׸� 1���� ���� ��
#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
#define PI_2			6.283185308f


#define FLOAT_EPSILON	0.0001f

#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1,f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//�� �� ������ �Ÿ��� ���Ѵ�.
	float getDistance(float startX, float startY, float endX, float endY);
	// start���� end������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float startY, float endX, float endY);

}