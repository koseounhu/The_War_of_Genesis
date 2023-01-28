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

    // �����쿡�� �ο��� ���� �ĺ� ��ȣ
    HANDLE file;
    WORD BOM = 0xFEFF;      
    DWORD dwBytes = 0;
    DWORD dwRead;

    /*
    �� BOM (Byte Of(Order) Mark) ����Ʈ ����ǥ�� , �����Ҷ� �޸� � ������� ���������� ���� ǥ�� (��->�� / ��->�� ���)
    
    - ��ǻ�ʹ� �����͸� �޸𸮿� ������ �� ����Ʈ ������ ������ ������ �Ѵ�.
    - ������ �����ڵ��� ��� ���ڵ� ����̳� ����� ��Ŀ� ���� BOM�� �ʿ��� ��찡 �ִ�.

    �� �����찡 ����ϴ� ����� UTF-16 (U+FEFF) -> BOM

    - ����Ʈ�� ����Ǵ� ������ ���� �� �����(���ۺ��� �� , �¿��� ��� ����), ��Ʋ �����(������ ���� , �쿡�� �·� ����)���� ������. -> �������α׷��Ӱ� ���� ȸ���������� �� ���� ����Ѵ�.
    
            - �� ����� (Big _endian) �� -> ��
                �� �� ����� ����� ���� �ּҿ� �������� ���� ����Ʈ ���� �����ϴ� ���
                �� �޸𸮿� ���������� ����Ǳ⶧���� �״�� ���� ���� �ִ�.
                    �� ����� ���ϴ�.

            - ��Ʋ ����� (Little Endian) (�� <- ��)
                �� ��Ʋ ����� ����� ���� �ּҿ� �������� ���� ����Ʈ�� �����ϴ� ���
                �� ��� ����� �д� ������ ������ �о�� �ϱ� ������ ���ټ��� ��������.

    - ���� ������ ���� ���ʿ� 0xFEFF�� ���̳ʸ� �������� ä���ؼ� (BOM)���Ŀ� ���� ���ڳ� ���ڿ��� �о� ���̰� �ϴ� ��Ķ����� ����Ѵ�.
    */
   
    /*
    CreateFile : ���� ����� ��ġ�� ����ų� �о�´�.
                ��� �� �� �ִ� Handle�� ��ȯ�Ѵ�.

    ����:
    1. �����ϰų� ���� �� ������ �̸�
    2. ���� ���� Ÿ�� (������ write , �������� read)
    3. ������ ������ ���� ���� (0 -> ���� x)
    4. �ڽĿ��� ��ӿ��� (3,4���� ���ӿ��� ���� ������)
    5. ���� ������� ����
        �� CREATE_ALWAYS : ���ο� ���� ���� -> ������ ���� ����� ���� ����
    6. ������ �ɼ� �� ����( �б����� / �������� ���)
        �� FILE_ATTRIBUTE_NORMAL : �Ϲ����� �Ӽ��� ����Ѵ�. (�б�� ���� ��� ����)
    7. ���Ͽ� ���� �Ӽ���(���� ���� ��� ���) -> �����ɶ� ����ó�� ���ټ��ִ�.
    */





    // ���� ����
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

    // INVALID_HANDLE_VALUE : �ڵ� �ʱ�ȭ�� ����Ѵ�.
    // ���� cratefile�� ������ ����� �޼��� �ڽ� ����
    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "���� ���� ���� ", "����", MB_OK);
    }
    else
    {
        // ���� �ۼ�
        // ���� : CreateFile���� �Ҵ�� �ڵ�, ���Ͽ� ������� ��Ʈ����,
        //       �󸶳� �а� ���������� ���� ũ��
        //       �󸶳� �а� �� �������� ���� ��ȯ�� (�ּ�)
        // WriteFile(file, &BOM, 2, &dwBytes, NULL);

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

    // GENERIC_READ : �Ϲ����� �б� ���� (������ �ִ� ���� �ϴ� �аٴ�)
    // OPEN_EXISTING : ������ ������ ���ڴ�.

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
        MessageBox(_hWnd, "���� ���� ���� ", "����", MB_OK);
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


    /*
    ios::in      ������ �б⸸ ������ ���� �����ϰڴ�.
    ios::out     ������ ���⸸ ������ ���� �����ϰڴ�.
    ios::ate     ������ ������ �� ������ ������ ���� �����͸� �̵� ��Ų��.
    ios::app     �ش� ���Ͽ� �� ���������� �����͸� �߰��Ѵ�.
    ios::trunc   ������ ������ �ش� ������ ��� �����͸� ���� ����
    ios::binary  ���̳ʸ����� ����(���� ����)
    */

    fileIn.open(fileName, ios::in);

    char data;
    string jsonStr;
    // �ݺ��� ���鼭 �����͸� ����ִ´�.
    while (fileIn.get(data))
    {
        jsonStr += data;
    }
    fileIn.close();

    // ������ ��ȯ
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
        MessageBox(_hWnd, "�����Ͱ� ����.", "���", MB_OK);
        return NULL;
    }
    
    Json::Reader reader;
    Json::Value root;


    // ��
    // �÷����� �ٸ� ��� �ľ�, �ĽḦ ����Ͽ� �����͸� ��ȯ�Ͽ� �Ѱ�����Ѵ�.
    // �Ľ� : Ư�� ������ �о� �鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ��� �� �� �ְ� ������ ǥ�� ������� ��ȯ�� �ִ� ��
    // �ļ� : �Ľ��� �ϴ� ���μ���


    bool parsingRet = reader.parse(jsonStr, root);

    if (!parsingRet)
    {
        string errMsg = reader.getFormatedErrorMessages();
        MessageBox(_hWnd, errMsg.c_str(), "����", MB_OK);     // �����޼����� ��ٸ� �״�� �����ؼ� ���ۿ� �־� �˻��غ��� �� ��õ
        PostQuitMessage(0);
    }

    return root;
}
