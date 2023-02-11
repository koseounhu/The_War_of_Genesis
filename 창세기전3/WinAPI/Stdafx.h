#pragma once

//��� ����
// �� 4005: DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ���� ��µǴ� ���
#pragma warning(disable : 4005)

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN
// GDI+�� ����Ϸ��� ������� �����;� �Ѵ�
// �� <ole2.h>

//! Windows ��� ����
#include <windows.h>

//! ������ �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! ���̺귯�� ��ũ
#pragma comment (lib, "msimg32.lib") //����ũ�μ���Ʈ(ms) �̹���(img) 32��Ʈ(32) ���̺귯��
#pragma comment (lib, "winmm.lib") 
#pragma comment (lib, "lib/FMOD/fmodex64_vc.lib.") 
#pragma comment (lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")

//! �ܺ� �������
#include "inc\FMOD\fmod.hpp"			// �������� / �������ؼ� \ �����
#include "JsonCPP\include\json\json.h"			// �������� / �������ؼ� \ �����



// =====================
//! C ��Ÿ�� ��� ����
// =====================
#include <SDKDDKVer.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <MMSystem.h>

// =====================
//! C++ ��Ÿ�� ��� ����
// =====================
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <bitset>
#include <cassert>
#include <algorithm>		
#include <functional>		
#include <fstream>			// ���� ����¿� ���� �������� ���մ� �������
#include <queue>			// ���� �ְ� ���ִµ� ����ȭ�� stl






using namespace std;


// =====================
//! ����� ���� �������
// =====================
#include "CommonMacroFunction.h"  
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"
#include "GOLD.h"

using namespace MY_UTIL;

// =====================
//! �̱���
// =====================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
#define GOLD GOLD::getSingleton()

//==============================
// # ��ũ�� # (������â �ʱ�ȭ)
//==============================

//! ��ü ȭ��
//#define FULL_SCREEN

#ifdef FULL_SCREEN

#define WIN_NAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 0
#define WINSTART_Y 0
//GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ�Ѵ�.
	//�� SM_CXSCREEN: ���� ȭ�� ���� �ػ� x�� ��ȯ
	//�� SM_CYSCREEN: ���� ȭ�� ���� �ػ� y�� ��ȯ
#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
//WS_POPUPWINDOW: �˾� ������ ����
// WS_MAXIMIZE: ������ ������ �ִ�ȭ
#define WINSTYLE WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WIN_NAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 400
#define WINSTART_Y 200
#define WINSIZE_X 1024
#define WINSIZE_Y 768
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#endif

//==============================
// # ��ũ�� �Լ� #
//==============================
#define SAFE_DELETE(p)       {if(p){delete(p); (p) = nullptr;}}   //�����ϰ� �ʱ�ȭ
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}  //���� ��ü�� ���
#define SAFE_RELEASE(p)      {if(p) {(p)->release();(p)=nullptr;}

//==============================
// # ���� ���� #
//==============================
// extern Ű����� �ٸ� ��� or cpp���� ������ �����ϱ� ���� ����Ѵ�.
// �� ���� ������ Ű���带 �����ص� �⺻���� externȭ �Ǵ� ��찡 �ִ�.(VS������ ���� �ٸ�)
extern HINSTANCE _hInstance;
extern HWND _hWnd;
//X��ǥ�� Y��ǥ�� ����� ��ǥ�� ������ �� ��� -2D���� ��ǥ ǥ�� ����
extern POINT _ptMouse;
