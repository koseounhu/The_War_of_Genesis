#pragma once
#include "SingletonBase.h"

#define DATA_FILE_NAME "SaveData.json"


/*
* ���� ��������� ���
����Ʈ , ���� �ý��� , ���̾�α� ��� ����� ���� ����
�� �ѹ��̻� ����ϴ� ���� ����
STL�� ������ ����ϴ°��� ȿ���� ����.
*/

#pragma region ���̽�
/*
	�� ���̽� (JSON (JavaScript Object Notation))
	
	- ���̽��� ��ü�� ������ �Ӽ��� �ؽ�Ʈ �������� �����ϱ����� ��ȵ� ����̴�.
		�� ���ͳݿ��� �ڷḦ �ְ� ���� �� �� �ڷḦ ǥ���ϴ� ������� �ַ� ����� �ȴ�.
	
	- �ڷ��� ������ ū ������ ������ Ư�� ��ǻ�� ���α׷��� �������� ǥ���ϴµ� �����ϴ�.
	
	- ���̽��� ������ �ڹ� ��ũ��Ʈ�� ���� ������ �������� ���α׷��� �� �÷����� �������̹Ƿ� 
		C, C++ C#, �ڹ�, �ڹٽ�ũ��Ʈ, ��, ���̽�, ��� ���
		���� ���� ����� �ǰ� �ִ�.
	
	- XML, HTTP, CSV ��� ���� "�Ϲ�����" ȯ�濡�� �� ������.

	- ������ (JSON��, ������, ) ��Ÿ�� ģ�� ������ �ֻ����� �Ұ�
	- CSV�� , �������� ������� ©�� �Ѱ��ش�.

	- ���̽� ���Ŀ��� ����ϴ� ��ȣ�� �ǹ̴� ������ ����.
	{} : ��ü
	Ű : �� -> ��ü�� ������ �Ӽ�
	"" : ���ڿ� ������
	[] : �迭
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
	void saveJsonFile(char* fileName, Json::Value root);		// ����� ���� ���� ������ root�� ���� ���� �ʴ´�.

	Json::Value loadJsonFile(char* fileName);





	JsonSaveLoader() {}
	~JsonSaveLoader() {}
};

