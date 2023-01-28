#pragma once
#include <Windows.h>
/*
	▶순수 가상 함수
	ㄴ 함수의 구현부가 없고 선언부가 =0으로 끝나느 가상함수를 뜻한다.
	ㄴ 부모 클래스에서 순수 가상함수를 선언하면 자식 클래스에서는 반드시 재정의한 함수를 멤버로 가지고 있어야 한다.
	

	▶ 추상 클래스(Abstract Clsaa)
	- 순수 가상 함수가 1개 이상 있는 클래스를 뜻한다.

	▷ 특징
	1. 객체를 생성할 수 없다. (단, 포인터 변수는 만들 수 있다.)
		ㄴ 추상 클래스로 지정한 객체(클래스)는 인스턴스를 만들 수 없다.
		ㄴ 추상 클래스의 자식 클래스를 통해 인스턴스를 생성할 수 있다.

	2. 멤버 변수 or 일반 멤버 함수가 포함된 여부와 상관없이 순수 가상함수를 1개 이상 가지고 있다면 추상 클래스의 조건에 해당된다.

	ex)
	//C++
	class IWindowMessage abstract
	{

	};

	//C#
	abstract class ITessllation
	{

	};


	▶ 인터페이스(Interface)
	- OCP (개방 폐쇄의 원칙)
		ㄴ 자신의 확장에는 열려 있고 주변의 변화에 대해서는 닫혀 있어야 한다.
	- 순수 가상함수로 이루어진 클래스를 인터페이스라고 한다.
	- 인터페이스의 개념은 하위 클래스에서 반드시 정의해야 할 함수를 정해주는 클래스라고 할 수 있다.
	- C++ 언어는 인터페이스라는 개념을 공식적 기능으로 지원하지 않는다.
	- 표기법: 파스칼(I)
	※ 인터페이스(순수 가상함수 설계) -> (상속) 추상 클래스 (기본 기능 구현) -> (상속) 일반 클래스(순수 가상함수 재정의)

	▷ 특징
	- 멤버 변수 및 함수를 포함할 수 없다. (정적 함수 포함)
	- 속성을 정의하는 한정자를 사용할 수 없다. 
		ㄴ ex. const
	- 기본 클래스를 상속받을 수 없다.
	- 순수 가상 함수만 포함 시켜야 한다.
	- 생성자 / 소멸자 / 연산자를 포함할 수 없다.
	- public 속성을 가지고 있어야 한다.

	//-> 한줄조사.
	▷ 장점
	중복로직 제거 / 유지보수 편함

	▷ 단점

	▶ 가상 소멸자(★)
*/

/*
__interface IGameClass
{
	void idle();
	void attack();
};

class CharacterChoices abstract : public IGameClass
{
private:
	//! Do Something
public:
	//! Do Something
};

//파생
class Warrior : public CharacterChoices
{
private:

public:
		virtual void idle();
};

//파생
class Wizard : public CharacterChoices
{
private:

public:
	virtual void idle();
};
*/

class IWindowMessage
{
public:
	/*
	// 순수 가상 함수 만드는 법
	virtual void IFunctionA() = 0;
	virtual void IFunctionB() = 0;
	virtual void IFunctionC() = NULL;
	virtual void IFunctionD() PURE; //개방폐쇄의 원칙때문에 PURE 매크로는 GameNode에 직접 쓸 수 없음.
	virtual void IFunctionE() abstract;
	*/
	IWindowMessage();
	~IWindowMessage();
};

