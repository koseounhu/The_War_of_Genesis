#pragma once
#include "SingletonBase.h"

#define DATA_FILE_NAME "SaveData.json"


/*
* 파일 입출력으로 사용
퀘스트 , 저장 시스템 , 다이얼로그 등등 사용할 곳은 많다
꼭 한번이상 사용하는 것이 좋다
STL과 물려서 사용하는것이 효율이 좋다.
*/

#pragma region 제이슨
/*
	▶ 제이슨 (JSON (JavaScript Object Notation))
	
	- 제이슨은 객체의 구조와 속성을 텍스트 형식으로 전달하기위해 고안된 방식이다.
		ㄴ 인터넷에서 자료를 주고 받을 때 그 자료를 표현하는 방법으로 주로 사용이 된다.
	
	- 자료의 종류에 큰 제한은 없으며 특히 컴퓨터 프로그램의 변수값을 표현하는데 적합하다.
	
	- 제이슨의 형식은 자바 스크립트의 구문 형식을 따르지만 프로그래밍 언어나 플랫폼에 독립적이므로 
		C, C++ C#, 자바, 자바스크립트, 펄, 파이썬, 루비 등등
		많은 언어에서 사용이 되고 있다.
	
	- XML, HTTP, CSV 등등 보다 "일반적인" 환경에서 더 빠르다.

	- 삼충이 (JSON충, 패턴충, ) 평타는 친다 하지만 최상위는 불가
	- CSV는 , 기준으로 밸류값을 짤라서 넘겨준다.

	- 제이슨 형식에서 사용하는 기호의 의미는 다음과 같다.
	{} : 객체
	키 : 값 -> 객체가 가지는 속성
	"" : 문자열 데이터
	[] : 배열
*/
#pragma endregion




class JsonSaveLoader : public SingletonBase <JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);


public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);		// 명령을 따로 주지 않으면 root를 통해 들어가지 않는다.

	Json::Value loadJsonFile(char* fileName);





	JsonSaveLoader() {}
	~JsonSaveLoader() {}
};

