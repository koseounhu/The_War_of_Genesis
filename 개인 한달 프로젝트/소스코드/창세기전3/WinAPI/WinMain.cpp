#include "Stdafx.h"
#include "MainGame.h"

// =================
// # 전역 변수 #
// =================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };
//TCHAR* pszSting = _T("Windows API");

// =================
// # 함수 전방선언 #
// =================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

/*
int WINAPI _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    TCHAR* lpszCmdParam,
    int       nCmdShow)
{

}
*/

//윈도우 메인 함수
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _mg = new MainGame();
    //해당되는 인스턴스를 전역변수에 담는다.
    _hInstance = hInstance;

    //윈도우 창 구조체 선언 및 초기화
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0; //클래스 여분 메모리
    wndClass.cbWndExtra = 0; //윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //백그라운드. GetStockObject() 동적할당 가능하게 확장한 함수.
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //마우스커서 아이콘
    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING); //아이콘
    wndClass.hInstance = hInstance; //원도우를 소유한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc; //윈도우 프로시져. 예외발생을 처리하기 위해 (WNDPROC)를 사용.
    wndClass.lpszClassName = WIN_NAME; //쿨래스 이름(윈도우 클래스 식별자 정보)
    wndClass.lpszMenuName = NULL; //메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우 스타일(윈도우 다시그리기 정보)

    //HRESULT hr;
    //hr = RegisterClass(&wndClass);
    //assert(SUCCEEDED(hr));
    //컴파일러는 오류가 있어도 끝까지 다 읽고 죽는다.
    //assert가 발동되면 컴파일러가 시동이 안 됨. 즉시 코드를 죽임.

    // 윈도우 클래스 등록
    RegisterClass(&wndClass);



#ifdef FULL_SCREEN == FULL_SCREEN

    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));
    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;
    dm.dmPelsWidth = 1980;
    dm.dmPelsHeight = 1020;
    dm.dmDisplayFrequency = 60;             //재생빈도 60Hz

    //우리가 설정한 플래그(옵션) 값 설정
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    //화면이 종료되면 원래 해상도로 복귀(자동으로)
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    // 화면에 보여줄 윈도우 창 생성
    _hWnd = CreateWindow
    (
        WIN_NAME, //윈도우 클래스 식별자
        WIN_NAME, //윈도우 타이틀 바 이름
        WINSTYLE, //윈도우 스타일
        WINSTART_X, //윈도우 화면 x좌표
        WINSTART_Y, //윈도우 화면 y좌표
        WINSIZE_X, //윈도우 화면 가로크기
        WINSIZE_Y, //윈도우 화면 세로크기
        NULL, //부모 윈도우 지정여부.
        (HMENU)NULL, //메뉴 핸들
        hInstance, //인스턴스 지정
        NULL //윈도우의 자식 윈도우를 생성하면 지정하고 아니라면 NULL. - 필요에 의해 사용하지만 지금은 NULL
    );

    // 클라이언트 영역의 사이즈를 정확히 잡는다.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#else

    // 화면에 보여줄 윈도우 창 생성
    _hWnd = CreateWindow
    (
        WIN_NAME, //윈도우 클래스 식별자
        WIN_NAME, //윈도우 타이틀 바 이름
        WINSTYLE, //윈도우 스타일
        WINSTART_X, //윈도우 화면 x좌표
        WINSTART_Y, //윈도우 화면 y좌표
        WINSIZE_X, //윈도우 화면 가로크기
        WINSIZE_Y, //윈도우 화면 세로크기
        NULL, //부모 윈도우 지정여부.
        (HMENU)NULL, //메뉴 핸들
        hInstance, //인스턴스 지정
        NULL //윈도우의 자식 윈도우를 생성하면 지정하고 아니라면 NULL. - 필요에 의해 사용하지만 지금은 NULL
    );

    // 클라이언트 영역의 사이즈를 정확히 잡는다.
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

    // 화면에 윈도우창 보여주기
    ShowWindow(_hWnd, nCmdShow);

    //메인 게임 클래스 초기화 실패 시 종료
    if (FAILED(_mg->init()))
    {
        return 0;
    }

    //MSG: 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체.
    MSG message;

    // 2. 메시지 루프
    
    //게임용
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT) break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TIMEMANAGER->update(60.0f);
            _mg->update();
            _mg->render();
        }
    }
    
    ////PM_REMOVE: 정수 1을 16진수로 바꿔 놓은 것. -> 속도를 올리기 위함.
    ////일반 프로그래밍
    //while (GetMessage(&message, 0, 0, 0))
    //{
    //    TranslateMessage(&message);
    //    DispatchMessage(&message);
    //}

    _mg->release();
    //윈도우 클래스 등록 해제
    UnregisterClass(WIN_NAME, hInstance);
    return message.wParam;
}

//윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, IMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    //실제 윈도우 크기 조절
    //AdjustWindowRect() : 대상 객체, 사용할 윈도우 스타일, 메뉴 여부
    AdjustWindowRect(&rc, WINSTYLE, false);

    //얻어온 렉트의 정보로 윈도우 사이즈 셋팅
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
    //ZORDER : 물체들이 겹쳐졌을 때 레이어 순서 정리를 위해 사용(랜더링). 게임에서 많이 쓰인다.
    //우리 화면을 제일 앞에 띄우겠다. (지금)
}