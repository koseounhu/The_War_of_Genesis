#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager :public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;




public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT changScene(string sceneName);
	
	// friend : 단방향 참조
	// 이미지를 불러오다 상속구조가 문제생기면 뚫고 들어가라 
	// 콜백 = 델리게이트
	// LPVOID : void* 보이드 포인터 어떤게 들어올지모르지만 반환할 준비를 하겟다 = 어떤타입으로도 반환가능
	// 로딩스레드 함수
	// 
	friend DWORD CALLBACK loadingThread(LPVOID prc);



	SceneManager() {}
	~SceneManager() {}
};

