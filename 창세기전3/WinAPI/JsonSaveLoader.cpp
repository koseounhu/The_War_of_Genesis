#include "Stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
    // ! Do Nothing
    return S_OK;
}

void JsonSaveLoader::release(void)
{// ! Do Nothing
}


void JsonSaveLoader::saveString(char* fileName, string data)
{
    TCHAR* buf = (TCHAR*)data.c_str();

    // 윈도우에서 부여한 고유 식별 번호
    HANDLE file;
    WORD BOM = 0xFEFF;      
    DWORD dwBytes = 0;
    DWORD dwRead;


    // 파일 생성
    file = CreateFile
    (
        fileName,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL    
    );

    // INVALID_HANDLE_VALUE : 핸들 초기화에 사용한다.
    // 위에 cratefile이 문제가 생길시 메세지 박스 생성
    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "생성 파일 에러 ", "에러", MB_OK);
    }
    else
    {
        WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);
        CloseHandle(file);
    }

}


string JsonSaveLoader::loadString(char* fileName)
{
    TCHAR buf[8192];
    ZeroMemory(buf, sizeof(buf));

    HANDLE file;
    DWORD dwBytes;

    file = CreateFile
    (
        fileName,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );


    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "생성 파일 에러 ", "에러", MB_OK);
        return "";
    }
    else
    {
        ReadFile(file, buf, 8192, &dwBytes, NULL);
        CloseHandle(file);
    }


    return string(buf);
}


void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
    ofstream outFile(fileName);

    outFile << data << endl;

    outFile.close();
}



string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{

    ifstream fileIn;


    fileIn.open(fileName, ios::in);

    char data;
    string jsonStr;
    // 반복을 돌면서 데이터를 집어넣는다.
    while (fileIn.get(data))
    {
        jsonStr += data;
    }
    fileIn.close();

    // 데이터 반환
    return jsonStr;
}


void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
    Json::StyledWriter write;
    string outputConfig = write.write(root);
    saveStringWithFileStream(fileName, outputConfig);

}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
    string jsonStr = loadStringWithFileStream(fileName);
    if (jsonStr == "")
    {
        MessageBox(_hWnd, "데이터가 없다.", "경고", MB_OK);
        return NULL;
    }
    
    Json::Reader reader;
    Json::Value root;




    bool parsingRet = reader.parse(jsonStr, root);

    if (!parsingRet)
    {
        string errMsg = reader.getFormatedErrorMessages();
        MessageBox(_hWnd, errMsg.c_str(), "오류", MB_OK);     // 오류메세지가 뜬다면 그대로 복사해서 구글에 넣어 검색해보는 걸 추천
        PostQuitMessage(0);
    }

    return root;
}
