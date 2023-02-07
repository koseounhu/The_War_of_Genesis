#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	_tick = _alpha = _count = 0;
	_dia = new Dialogue;
	_dia->init();

	x = 470;
	y = 610;

	// ���̾�α� ���� ��Ʈ��
	_diaText.reset();
	_diaSound.reset();

	// ū�̹���
	_bigImageAlpha = 0;

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_dia);
}

void SecondScene::update(void)
{
	_tick++;

	// ���İ� ����
	/*if (_tick % 3 == 0)*/ _alpha++;
	if (_alpha >= 255)
	{
		_alpha = 255;
	}

	_dia->update();
	
}

void SecondScene::render(void)
{

	switch (_count)
	{
	case 0:
		IMAGEMANAGER->findImage("2_1")->alphaRender(getMemDC(), _alpha);
		// ���� ���
		if (!_diaSound[0]) SOUNDMANAGER->play("����Ʈ_�׿���", 1.0f);

		// ���� �߰� ��� �ȵǰ� ���� ��Ʈ��
		_diaSound.set(0, 1);

		if (_diaText.any()==0)
		{
			IMAGEMANAGER->findImage("����ƮĮ��")->render(getMemDC(), x + 150, y);
			IMAGEMANAGER->findImage("����Į")->render(getMemDC(), x, y);
		}


		if (_alpha == 255)
		{

			// 0�� ���̾�α�
			if (!_diaText[0])
			{
				// ū ĳ���� �̹��� ���
				if (SOUNDMANAGER->getLength("����Ʈ_�׿���") != SOUNDMANAGER->getPosition("����Ʈ_�׿���"))_bigImageAlpha += 5;
				if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
				IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

				// ���̾�α� â
				IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

				// ����Ʈ - �׿���
				_dia->drawTextNoSkip(0, 120, 590, 200, 200, 20, 255, 255, 255);

				if (SOUNDMANAGER->getLength("����Ʈ_�׿���") == SOUNDMANAGER->getPosition("����Ʈ_�׿���") && _diaText[0] == 0)
				{
					_bigImageAlpha -= 5;
					if (_bigImageAlpha < 0)
					{
						_diaText.set(0, 1);
						_diaText.set(1, 1);
						_bigImageAlpha = 0;
						_tick = 0;
					}
				}
				
			}
			

			// 1�� ���̾�α�
			if (_diaText[1])
			{
				if (_tick < 250)
				{
					// ū�̹���
					if (_tick < 150)_bigImageAlpha += 5;
					else if (_tick > 150)_bigImageAlpha -= 5;
					
					if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
					else if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

				
					IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);


					// ���̾�α� â
					IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

					// ���� - ...
					_dia->drawTextNoSkip(1, 120, 590, 200, 200, 20, 255, 255, 255);
				}
				
				
				else if (_bigImageAlpha>=0)
				{
					_diaText.set(1, 0);
					_diaText.set(2, 1);
					_tick = 0;
				}
			}

			// ����� ���� ���
			else if (_diaText[2])
			{
				if (_tick > 100 && _tick < 200)
				{
					IMAGEMANAGER->findImage("����̻���")->render(getMemDC(), x+170, y);
					IMAGEMANAGER->findImage("����_�����")->render(getMemDC(), x + 70, y - 20);
				}
				else if (_tick < 100)
				{
					IMAGEMANAGER->findImage("����̻���")->render(getMemDC(), x + 170, y);
					IMAGEMANAGER->findImage("����Į")->render(getMemDC(), x, y);
				}
				
				if (_tick > 200 && _tick < 400)
				{
					IMAGEMANAGER->findImage("����̻���")->render(getMemDC(), x + 170, y);
					IMAGEMANAGER->findImage("����_���Ķ�")->frameRender(getMemDC(), x + 70, y - 10, 0, 0);
				}
				else if (_tick > 400)
				{
					_diaText.set(2, 0);
					_diaText.set(3, 1);
					_tick = 0;
					_bigImageAlpha = 0;
				}
			}


			// 2�� ���̾�α�
			if (_diaText[3])
			{
				if (SOUNDMANAGER->getLength("����Ʈ_�װ͸���") != SOUNDMANAGER->getPosition("����Ʈ_�װ͸���"))
				{
					_bigImageAlpha += 5;
					if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
					IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

					// ���̾�α� â
					IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

					// ����Ʈ - �װ͸��� ..
					_dia->drawTextNoSkip(2, 120, 590, 200, 200, 20, 255, 255, 255);

					// ���� �߰� ��� �ȵǰ� ���� ��Ʈ��
					if (!_diaSound[1]) SOUNDMANAGER->play("����Ʈ_�װ͸���", 1.0f);
					_diaSound.set(1, 1);
				}
				else if (SOUNDMANAGER->getLength("����Ʈ_�װ͸���") == SOUNDMANAGER->getPosition("����Ʈ_�װ͸���"))
				{
					_diaText.set(3, 0);
					_diaText.set(4, 1);
					_bigImageAlpha = 0;
					_tick = 0;
				}

			}

			else if (_diaText[4])
			{
				_bigImageAlpha+=2;
				IMAGEMANAGER->findImage("����̻���")->render(getMemDC(), x + 170, y);
				IMAGEMANAGER->findImage("����_���Ķ�")->frameRender(getMemDC(), x + 70, y - 10, 1, 0);
				IMAGEMANAGER->findImage("�Ͼ����")->alphaRender(getMemDC(), _bigImageAlpha);

				if (_bigImageAlpha >= 255)
				{
					_bigImageAlpha = 0;
					_count++;
				}
			}

			
		}

		break;

	case 1:
		IMAGEMANAGER->findImage("2_2")->render(getMemDC());

		break;

	case 2:
		IMAGEMANAGER->findImage("2_3")->alphaRender(getMemDC(), _alpha);

		break;

	case 3:
		IMAGEMANAGER->findImage("2_4")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 4:
		IMAGEMANAGER->findImage("2_5")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 5:
		IMAGEMANAGER->findImage("2_6")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 6:
		IMAGEMANAGER->findImage("2_7")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 7:
		IMAGEMANAGER->findImage("2_8")->alphaRender(getMemDC(), _alpha);
		break;

	case 8:
		IMAGEMANAGER->findImage("2_9")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 9:
		IMAGEMANAGER->findImage("2_2")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 10:
		IMAGEMANAGER->findImage("2_10")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 11:
		IMAGEMANAGER->findImage("3_1")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 12:
		IMAGEMANAGER->findImage("4_1")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 13:
		IMAGEMANAGER->findImage("4_2")->alphaRender(getMemDC(), _alpha);
		break;
	
	case 14:
		IMAGEMANAGER->findImage("4_3")->alphaRender(getMemDC(), _alpha);
		break;

	case 15:
		IMAGEMANAGER->findImage("4_4")->alphaRender(getMemDC(), _alpha);
		break;

	default:
		break;
	}

	if (_count > 0 && _count<11)
	{
		_bigImageAlpha+=2;
		IMAGEMANAGER->findImage("�Ͼ����")->alphaRender(getMemDC(), _bigImageAlpha);
		if (_bigImageAlpha >= 255)
		{
			_bigImageAlpha = 0;
			_count++;
		}
	}



}

//void SecondScene::drawText(char* string, int x, int y, int jsonNum)
//{
//	char str[256];
//	queue<Dialog2*>* temp = _diaSample->getDialog2();
//	Dialog2* node = temp->front();
//	sprintf_s(str, "%s", node->getName().c_str());
//	FONTMANAGER->drawText(getMemDC(), 120, 600, 20, 52, 255, 192, "����", true, str);
//	sprintf_s(str, "%s", node->getText().c_str());
//	FONTMANAGER->drawText(getMemDC(), 140, 630, 20, 255, 255, 255, "����", true, str);
//
//
//	if (_tick % 3 == 0) _dialogue[jsonNum].tick++;
//
//	if(_dialogue[jsonNum].tick > strlen(_dialogue[jsonNum].text))
//
//
//
//
//}

