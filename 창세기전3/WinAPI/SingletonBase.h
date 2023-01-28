#pragma once

#pragma region 디자인 패턴 + 싱글톤
/*
▶ 디자인 패턴
- 객체 지향 프로그래밍 설계 단계에서 자주 발생하는 or 알려진 문제들을 피하기 위해 사용하는 패턴을 의미한다.

▷ 장점
1. 의사 소통 간결화로 효율 증가(작업 속도 UP) 
	ㄴ ex. 우리 이번에 작업해야 할 기능 데코레이터로 처리합시다.

2. 평준화 되고 안정적인 코드 동작성
	ㄴ 많은 프로그래머가 이미 동일한 증상을 겪어 보았기 때문에 시간이 지남에 따라 해결 방안도 대부분 나온 상태.

3. 프로그래밍을 작성하는 데 있어 디자인 타임에서의 다양한 상황에 대한 가이드 및 방향성 제시
	ㄴ 경험이 부족하다 하더라도 이미 어느 정도의 성능과 효율이 보장된 디자인 패턴을 사용하면 좋다.

▷ 단점
1. 디자인 패턴은 코드를 설계하고 작성하는 하나의 방법일 뿐. 패턴병 조심

2. 대부분의 디자인 패턴은 원본 부분과 활용 부분이 나뉘어져 있기 때문에 코드 간결화를 생각한다면 고민이 필요하다.


▶ 싱글톤 (★)
- 프로젝트 전체에서 한 개만 존재해야 하는 객체나 클래스, 또는 프로젝트 전체에서 공유하는 클래스에 적용할 수 있는 패턴.

▷ 장점
- 한번의 new를 통해서 객체를 생성하며 만약 프로젝트 어느 곳에서도 사용하지 않고 있다면 인스턴스를 생성하지 않기 때문에 메모리 낭비를 방지할 수 있다. (싱글톤을 템플릿으로 구현하기 때문에 템플릿의 장점)

▷ 단점
- 싱글톤은 대부분 전역변수로 처리하는 경우가 많기 때문에 코드에 대해 알아보기가 어려워지는 상황이 생길 수 있다.
- 싱글톤 인스턴스에게 너무 많은 데이터가 공유된다면 결합도가 높아져 유지보수가 힘들다.
*/
#pragma endregion

template <class T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//싱글톤 자겨오기
	static T* getSingleton(void);
	//싱글톤 메모리에서 해제
	void releaseSingleton(void);
};

template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	//싱글톤 없으면 새로 생성
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면 메모리에서 해제
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}