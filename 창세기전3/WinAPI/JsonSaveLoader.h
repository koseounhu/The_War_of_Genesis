#pragma once
#include "SingletonBase.h"

#define DATA_FILE_NAME "SaveData.json"



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

