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

	string _reservationScene;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT changScene(string sceneName);
	HRESULT changScene(string loadingScene, string reservationScene);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	string getReservationScene(void) { return _reservationScene; }

	SceneManager() {}
	~SceneManager() {}
};

