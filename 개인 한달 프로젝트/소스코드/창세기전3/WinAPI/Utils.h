#pragma once
// ==================================================
// # Utils(간소화 하고 싶거나 or 수학적 기능을 모아둔다.
// ㄴ 안 쓰면 주석치고 빼버려서 메모리관리하는 게 베스트
// ==================================================

//디그리 1도의 라디안 값
#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
// PI * 2로 쓰지 않는 이유는 연산을 제외하기 위해서.
// 수학은 상수화 시켜놓는 게 베스트.
// 연산 속도는 덧셈이 가장 빠르고 나눗셈이 가장 느림.
// 나눗셈은 반복이 돌기 때문. / 소숫점 들어있으면 특히
#define PI_2			6.283185308f

#pragma region
/*
	▶ 앱실론 (Epsilon)

	- 부동 소수점은 실수를 정확히 표현할 수 없는 문제를 가지고 있다.
	  ㄴ 왜냐하면 수학적으로 실수는 무한한데 이 실수를 유한한 비트로 표현하기 위해서는 컴퓨터가 어쩔 수 없이 근사치(값)로 표현해야 하기 때문.
	- 이러한 구조적 문제로 발생하는게 부동소수점 반올림 오차
	- 이러한 특성때문에 필연적으로 오차 범위가 발생하는데 정확한 계산을 위해서 상수로 정의된 값을 사용한다.
	- 2D는 크게 인식을 못하는 경우가 많지만 3D 같은 경우는 결과값이 달라질 수 있다.
*/
#pragma endregion

#define FLOAT_EPSILON	0.0001f

// 실수를 정수형으로 변환 (캐스팅)
// 바이트가 늘어나면 업캐스팅, 바이트가 줄어들면 다운캐스팅
// static_cast<자료형>는 C++에서 추가되었다. 논리적으로 가능하면 바꿔주고 아니면 안바꿔준다.
// (자료형) 강제 형변환. 무시하고 바꿔버린다.
/*
▶ 캐스팅 연산자 종류

1. static_cast
2. const_cast
3. dynamic_cast
4. reinterpret_cast : 개념만 이해.
1,3 자주사용
2 상수이니 유저이름에서 사용
*/
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
// 두 실수가 같은지 비교
// ㄴ Fabs는 소수점 차의 절대값 반환
#define FLOAT_EQUAL(f1,f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다.
	float getDistance(float startX, float startY, float endX, float endY);
	// start부터 end까지의 각을 라디안으로 구한다.
	float getAngle(float startX, float startY, float endX, float endY);

}