#pragma once



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