#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

// 함수에 종속시키지 않았기때문에 클래스가 호출될때 무조건 실행된다.
// 정적 변수 !?
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;


DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 모호함을 없애기 위해 SceneManager::을 계속 호출해주고 있다.
	// 컴파일에게 헷갈리지 말라고 알려주는 것

	SceneManager::_readyScene->init();
	SceneManager::_currentScene = SceneManager::_readyScene;

	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;



	return 0;
}


HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;



	return S_OK;
}

void SceneManager::release(void)
{
	// 1.
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}

		else ++miSceneList;
	}
	_mSceneList.clear();


	//// 2. C++에서는 절대 하면안된다 -> 오류가나면 어디서 오류가 낫는지 알수가 없다 
	//for each (auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}
}

void SceneManager::update(void)
{
	if (_currentScene)_currentScene->update();

}

void SceneManager::render(void)
{
	if (_currentScene)_currentScene->render();
}

GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	if (!scene)return nullptr;
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode* scene)
{

	if (!scene)return nullptr;
	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::changScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end())return E_FAIL;
	if (find->second == _currentScene)return S_OK;

	// 새롭게 변경되는 씬을 찾았다면 초기화를 한다.
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}






	return E_FAIL;
}
