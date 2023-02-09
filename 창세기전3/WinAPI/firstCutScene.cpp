#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_dia = new Dialogue;
	_dia->init(1);

	// ����Ʈ������
	_verX = 280;
	_verY = 400;
	_verFrame = 0;

	// ���� ������
	_salX = 250;
	_salY = 600;
	_saraFrame = 0;

	// �ζ� ������ 
	_dieFrame = 0;
	// ��ü ƽ
	_tick = 0;

	// �ζ� ������
	_saraFrame = 0;

	// ���� ��� ����
	_BGalpha = 0;

	// ���̾�α� ī��Ʈ
	_diaCount = 0;

	// ū�̹���
	_bigImageAlpha2 = _bigImageAlpha = 0;

	// ���̾�α� ���� �ʱ�ȭ
	_diaSound.reset();

	// ������ ����
	_lastAlpha = 255;

	return S_OK;
}

void firstCutScene::release(void)
{
	SAFE_DELETE(_dia);
}

void firstCutScene::update(void)
{
	_tick++;

	// ���ι�� ����
	_BGalpha++;
	if (_BGalpha >= 255) _BGalpha = 255;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stopAllSound();
		_diaCount = 22;
	}

	_dia->update();

}

void firstCutScene::render(void)
{
	// �ζ� �ױ� ������ ���׷��ֱ�
	if (!_diaSound[29])
	{
		IMAGEMANAGER->findImage("�ƽŹ��")->alphaRender(getMemDC(), _BGalpha);
		
		if (!_die)
			IMAGEMANAGER->findImage("�ζ�����")->frameRender(getMemDC(), 180, 380, _saraFrame, 0);

		if (_verX > 0)
			IMAGEMANAGER->findImage("����_���2")->frameRender(getMemDC(), _salX, _salY, 0, 3);
		else if (_dieFrame ==0)
			IMAGEMANAGER->findImage("����_�ȱ�2")->frameRender(getMemDC(), _salX, _salY, _salFrame, 3);


		

		// �������
		if (!_diaSound[30])
		{
			SOUNDMANAGER->play("1���ó������������", 0.1f);
			_diaSound.set(30, 1);
		}
	}
	if (_diaCount >= 18)
	{
		IMAGEMANAGER->findImage("2���������������")->alphaRender(getMemDC(), _lastAlpha);
	}

#pragma region �ζ� �ױ� ��
// ����Ʈ - ��ٸ����վ���
	if (_diaCount == 0)
	{
		if (_BGalpha < 255)_tick = 0;
		if (_BGalpha == 255)
		{
			// ĳ���� ���� ����
			if (_tick < 200)
			{
				_bigImageAlpha += 5;
				if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
			}
			else if (SOUNDMANAGER->getLength("��ٸ����վ���") == SOUNDMANAGER->getPosition("��ٸ����վ���"))
			{
				_bigImageAlpha -= 5;
				if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			}
			IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

			//���̾�α� ����
			if (!_diaSound[0])
			{
				_diaSound.set(0, 1);
				SOUNDMANAGER->play("��ٸ����վ���", 1.0f);
			}

			// ���̾�α� â
			IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

			_dia->drawTextNoSkip(_diaCount, 120, 590, 200, 200, 25, 255, 255, 255);

			// ���� �ѱ��
			if (_bigImageAlpha == 0)
			{
				_bigImageAlpha = 0;
				_diaCount++;
				_tick = 0;
			}

		}
	}

// ���� - ...
	else if (_diaCount == 1)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 200, 200, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// ����Ʈ - �������� ~~~
	else if (_diaCount == 2)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("��������") == SOUNDMANAGER->getPosition("��������"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[1])
		{
			_diaSound.set(1, 1);
			SOUNDMANAGER->play("��������", 1.0f);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// �ζ� - ����� ...
	else if (_diaCount == 3)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("�ζ�-����") == SOUNDMANAGER->getPosition("�ζ�-����"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("�ζ�")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[2])
		{
			_diaSound.set(2, 1);
			SOUNDMANAGER->play("�ζ�-����", 1.0f);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// ���� �������ÿ�
	else if (_diaCount == 4)
	{
	// ĳ���� ���� ����
	if (_tick < 200)
	{
		_bigImageAlpha += 5;
		if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
	}
	else if (SOUNDMANAGER->getLength("�ζ��ڵ�������ÿ�") == SOUNDMANAGER->getPosition("�ζ��ڵ�������ÿ�"))
	{
		_bigImageAlpha -= 5;
		if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
	}

	// ĳ���� �̹���
	IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

	//���̾�α� ����
	if (!_diaSound[3])
	{
		_diaSound.set(3, 1);
		SOUNDMANAGER->play("�ζ��ڵ�������ÿ�", 1.0f);
	}

	// ���̾�α� â
	IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
	// ���̾�α� �ؽ�Ʈ
	_dia->drawTextNoSkip(_diaCount, 120, 590, 500, 500, 25, 255, 255, 255);

	if (_bigImageAlpha == 0)
	{
		_bigImageAlpha = 0;
		_diaCount++;
		_tick = 0;
	}
	}

// ����Ʈ ����ΰ�
	else if (_diaCount == 5)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			if (_tick % 5 == 0)
			{
				if(_saraFrame < 2)	_saraFrame++;
			}
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (SOUNDMANAGER->getLength("����ΰ�") == SOUNDMANAGER->getPosition("����ΰ�"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[4])
		{
			_diaSound.set(4, 1);
			SOUNDMANAGER->play("����ΰ�", 1.0f);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

// �ζ� - ���� ����ġ
// ���� - ���� ...
// ����Ʈ - �������� ���ñ�
// ���� - �ֱ׷���
// 8�� ���� ���
// 9�� ��� ��
	else if (_diaCount ==6)
	{
		// ĳ���� ���� ����
		if (!_sara)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (_sara&&!_ver)
		{

			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)
			{
				_bigImageAlpha = 0;
				_ver = true;
			}
		}
		if (_ver)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}

		if (_sal)
		{
			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
		}

		// ĳ���� �̹���
		if(!_ver)IMAGEMANAGER->findImage("�ζ�")->alphaRender(getMemDC(), 500, 150, _bigImageAlpha);
		if(_sal) IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), -100, 100, _bigImageAlpha2);
		if (_ver) IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 550, 150, _bigImageAlpha);


		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 180, 580, 215);
		if (_sal) IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 50, 380, 215);


		// ���̾�α� �ؽ�Ʈ
		if(!_ver)_dia->drawTextNoSkip(6, 200, 590, 500, 500, 25, 255, 255, 255);
		else if (_ver)_dia->drawTextNoSkip(8, 200, 590, 800, 500, 25, 255, 255, 255);
		if (_sal && !_last) _dia->drawTextNoSkip(7, 70, 390, 500, 500, 25, 255, 255, 255);
		if (_last) _dia->drawTextNoSkip(9, 70, 390, 500, 500, 25, 255, 255, 255);



		

		//���̾�α� ����
		if (!_diaSound[5])
		{
			_diaSound.set(5, 1);
			SOUNDMANAGER->play("�ζ���ġ", 1.0f);
		}
		if (_sal && !_diaSound[6])
		{
			_diaSound.set(6, 1);
			SOUNDMANAGER->play("���򼳸�", 1.0f);
		}		
		if (_ver && !_diaSound[7])
		{
			_diaSound.set(7, 1);
			SOUNDMANAGER->play("����Ʈ����ź", 1.0f);
		}
		if (_last && !_diaSound[8])
		{
			_diaSound.set(8, 1);
			SOUNDMANAGER->play("����ֱ׷���", 1.0f);
		}

		// ���� ������ �Ұ� ��ȭ
		if (SOUNDMANAGER->getLength("�ζ���ġ") == SOUNDMANAGER->getPosition("�ζ���ġ"))
		{
			_sal = true;
		}
		if (SOUNDMANAGER->getLength("���򼳸�") == SOUNDMANAGER->getPosition("���򼳸�"))
		{
			_sara = true;
		}
		if (SOUNDMANAGER->getLength("����Ʈ����ź") == SOUNDMANAGER->getPosition("����Ʈ����ź"))
		{
			_last = true;
		}		
		if (SOUNDMANAGER->getLength("����ֱ׷���") == SOUNDMANAGER->getPosition("����ֱ׷���"))
		{
			_diaCount=10;
			_bigImageAlpha = _bigImageAlpha2 = 0;
			_ver = _sara = _sal = false;
			_tick = 0;
		}
	}

// 10�� ���
// 9�� ����
// ����Ʈ - ������
	else if (_diaCount == 10)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("����Ʈ������") == SOUNDMANAGER->getPosition("����Ʈ������"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[9])
		{
			SOUNDMANAGER->play("����Ʈ������", 1.0f);
			_diaSound.set(9, 1);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// ���� �� �ѱ��
		if(_bigImageAlpha==0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}
	}

// 11�����
// 10�� ���� ���
// ���� - Į�����ٴ�
	else if (_diaCount == 11)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("����Į����") == SOUNDMANAGER->getPosition("����Į����"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}
		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[10])
		{
			SOUNDMANAGER->play("����Į����", 1.0f);
			_diaSound.set(10, 1);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// ���� �� �ѱ��
		if (_bigImageAlpha==0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}

	}

// 13������ ���
// 12������ ���� ���
// �ζ� -�ȵǿ�
	else if (_diaCount == 12)
	{
	_saraFrame = 3;
	// ĳ���� ���� ����
		if (!_sara)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (_sal && !_sara)
		{
			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
		}
		else if (_sara)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <=0)_bigImageAlpha2 = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("�ζ�")->alphaRender(getMemDC(), 500, 150, _bigImageAlpha);
		if (_sal) IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), -100, 100, _bigImageAlpha2);


		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 180, 580, 215);
		if (_sal) IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 50, 380, 215);


		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 200, 590, 500, 500, 25, 255, 255, 255);
		if (_sal) _dia->drawTextNoSkip(13, 70, 390, 800, 500, 25, 255, 255, 255);





		//���̾�α� ����
		if (!_diaSound[11])
		{
			_diaSound.set(11, 1);
			SOUNDMANAGER->play("�ζ�ȵǿ�", 1.0f);
		}
		if (_sal&&!_diaSound[12])
		{
			_diaSound.set(12, 1);
			SOUNDMANAGER->play("����������", 1.0f);
		}
		// ���� ������ �Ұ� ��ȭ
		if (SOUNDMANAGER->getLength("�ζ�ȵǿ�") == SOUNDMANAGER->getPosition("�ζ�ȵǿ�"))
		{
			_sal = true;
		}
		
		if (SOUNDMANAGER->getLength("����������") == SOUNDMANAGER->getPosition("����������"))
		{
			_sara = true;
		}

		if (_bigImageAlpha == 0)
		{
			_diaCount=14;
			_bigImageAlpha = _bigImageAlpha2 = 0;
			_ver = _sara = _sal = false;
			_tick = 0;
		}
		
	}

// 14������ ���
// 13������ ����
// ����Ʈ - ü���ض�
	else if (_diaCount == 14)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("����Ʈü���ض�") == SOUNDMANAGER->getPosition("����Ʈü���ض�"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		
		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[13])
		{
			SOUNDMANAGER->play("����Ʈü���ض�", 1.0f);
			_diaSound.set(13, 1);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

		// ���� �� �ѱ��
		if (_bigImageAlpha == 0)
		{
			_diaCount++;
			_tick = 0;
			_bigImageAlpha = 0;
		}
	}

// 15������ ���
// 15������ ����
// �ζ��ڻ�
// ���� - �ȵ�
	else if (_diaCount == 15)
	{

		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		else if (_bigImageAlpha2 == 255)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}
		if (_bigImageAlpha == 0)
		{
			if (_tick % 5 == 0)
			{
				if(_saraFrame < 14)_saraFrame++;
				if (_saraFrame == 13)
				{
					_bigImageAlpha2 = 0;
				}
			}

			if (_saraFrame == 14)
			{
				IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _bigImageAlpha2);
				_bigImageAlpha2+=5;
				if (_bigImageAlpha2 >= 255)_bigImageAlpha2 = 255;
			}		
		}
		
		if (SOUNDMANAGER->getLength("�ζ��ڻ�") == SOUNDMANAGER->getPosition("�ζ��ڻ�"))
		{
			// 15�� ���̾�α׿����� ����ϱ����� �ӽ� ���
			_bigImageAlpha2 = 255;
		}

		if (!_diaSound[15] && _bigImageAlpha ==0)
		{
			_diaSound.set(15, 1);
			SOUNDMANAGER->play("����ȵ�", 1.0f);
		}

		// ĳ���� �̹���
		if (_bigImageAlpha != 0)
		IMAGEMANAGER->findImage("�ζ�")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[14])
		{
			_diaSound.set(14, 1);
			SOUNDMANAGER->play("�ζ��ڻ�", 1.0f);
		}

		// ���̾�α� â
		if (_bigImageAlpha != 0)
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		if (_bigImageAlpha != 0)
		_dia->drawTextNoSkip(_diaCount, 120, 590, 800, 500, 25, 255, 255, 255);

		// �ϳѱ��
		if (SOUNDMANAGER->getLength("����ȵ�") == SOUNDMANAGER->getPosition("����ȵ�"))
		{
			_bigImageAlpha = 0;
			_bigImageAlpha2 = 255;
			_diaCount++;
			_tick = 0;
		}
	}

// 16�� ���,���� ���
// ����Ʈ - ����
	else if (_diaCount == 16)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <= 0)_bigImageAlpha2 = 0;
		}
		IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _bigImageAlpha2);


		// ����ȭ�� ������� ��� ����
		if (_bigImageAlpha2 == 0)
		{
			if (_tick % 5 == 0)
			{
				_saraFrame++;
				if (_saraFrame > IMAGEMANAGER->findImage("�ζ�����")->getMaxFrameX())
					_saraFrame = IMAGEMANAGER->findImage("�ζ�����")->getMaxFrameX();
			}

			if (_saraFrame == IMAGEMANAGER->findImage("�ζ�����")->getMaxFrameX())
			{
				if (!_sal)
				{
					_bigImageAlpha += 5;
					if (_bigImageAlpha >= 255)
					{
						_bigImageAlpha = 255;
					}
				}
				else if (_sal)
				{
					_bigImageAlpha -= 5;
					if (_bigImageAlpha <=0)
					{
						_bigImageAlpha = 0;
					}
				}
				

				if (SOUNDMANAGER->getLength("����Ʈ����") == SOUNDMANAGER->getPosition("����Ʈ����"))
				{
					_sal = true;
				}

				// ĳ���� �̹���
				IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 150, _bigImageAlpha);

				//���̾�α� ����
				if (!_diaSound[16])
				{
					SOUNDMANAGER->play("����Ʈ����", 1.0f);
					_diaSound.set(16, 1);
				}

				// ���̾�α� â
				if(_bigImageAlpha != 0)
				IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);

				// ���̾�α� �ؽ�Ʈ
				if (_bigImageAlpha != 0)
				_dia->drawTextNoSkip(_diaCount, 120, 590, 1000, 500, 25, 255, 255, 255);

				if (_bigImageAlpha == 0)
				{
					_die = true;
					if (_tick % 5 == 0)
					{
						_verFrame++;
						if (_verFrame > IMAGEMANAGER->findImage("����Ʈ_�ȱ�")->getMaxFrameX())
							_verFrame =0;
					}

					
					IMAGEMANAGER->findImage("�ζ�������")->frameRender(getMemDC(), 213, 432, _dieFrame, 0);
					IMAGEMANAGER->findImage("����Ʈ_�ȱ�2")->frameRender(getMemDC(), _verX, _verY, _verFrame, 0);
					
					if (_verY < 500)
					{
						_verY += 5;
						_verX -= 5;
					}
					else
					{
						_verX -= 5;
					}
					if (_verX < 0 && _salY > 465)
					{
						if (_tick % 3 == 0)_salFrame++;
						if (_salFrame > 6)_salFrame = 0;
						_salY -= 5;
					}
					else if (_verX < 0 && _salY <= 465)
					{
						if (_tick % 15 == 0)_dieFrame++;
					}
				}

				// ���� �� �ѱ��
				if (_dieFrame >= 3)
				{
					_diaCount++;
					_tick = 0;
					_bigImageAlpha = 0;
					_BGalpha = 0;
					IMAGEMANAGER->findImage("��������")->render(getMemDC());
				}
			}
		}
	}
#pragma endregion

#pragma region �ζ� ������
// 17�� ���� ���
// ���� 30������ ���
// ���� - �̰� ������
	else if (_diaCount == 17)
	{
		// �������
		if (!_diaSound[22])
		{
			SOUNDMANAGER->stopAllSound();
			_diaSound.set(22, 1);
			SOUNDMANAGER->play("���ζ���������Ҷ�", 0.2f);
		}
		// ����̹��� ����
		// �ζ� ����
		if (!_diaSound[29])
		{
			_BGalpha += 5;
			if (_BGalpha >= 255)_BGalpha = 255;
		}		
		// �ζ� ������
		if (SOUNDMANAGER->getLength("�ζ�ȳ�")== SOUNDMANAGER->getPosition("�ζ�ȳ�"))
		{
			_BGalpha -= 5;
			if (_BGalpha <=0)_BGalpha = 0;

			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;

		}


		//IMAGEMANAGER->findImage("��������")->render(getMemDC());
		//IMAGEMANAGER->findImage("�ζ��������")->alphaRender(getMemDC(), _BGalpha);
		//
		//// ���� �̰� ������
		//if (_BGalpha == 255)
		//{


		//	if (!_diaSound[17])
		//	{
		//		_diaSound.set(17, 1);
		//		SOUNDMANAGER->play("�����̰Թ�����", 1.0f);
		//	}
		//}

		//// �ζ� �������� ���
		//if (SOUNDMANAGER->getLength("�����̰Թ�����") == SOUNDMANAGER->getPosition("�����̰Թ�����"))
		//{
		//	if (!_diaSound[18])
		//	{
		//		_diaSound.set(18, 1);
		//		SOUNDMANAGER->play("�ζ����",1.0f);
		//	}
		//}

		//// �ζ� �������� ����
		//if (SOUNDMANAGER->getLength("�ζ����") == SOUNDMANAGER->getPosition("�ζ����"))
		//{
		//	if (!_diaSound[19])
		//	{
		//		_diaSound.set(19, 1);
		//		SOUNDMANAGER->play("�ζ��������ð���", 1.0f);
		//	}
		//}

		//// ���� �����ʾ���
		//if (SOUNDMANAGER->getLength("�ζ��������ð���") == SOUNDMANAGER->getPosition("�ζ��������ð���"))
		//{
		//	if (!_diaSound[20])
		//	{
		//		_diaSound.set(20, 1);
		//		SOUNDMANAGER->play("���������ʾ���", 1.0f);
		//	}
		//}
		
		// �ζ� ����������
		if (SOUNDMANAGER->getLength("���������ʾ���") == SOUNDMANAGER->getPosition("���������ʾ���"))
		{

		}

		if (!_diaSound[21])
		{
			_diaSound.set(21, 1);
			SOUNDMANAGER->play("�ζ����������", 1.0f);
		}
		// ���� ������ȵǿ�
		if (SOUNDMANAGER->getLength("�ζ����������") == SOUNDMANAGER->getPosition("�ζ����������"))
		{
			if (!_diaSound[35])
			{
				_diaSound.set(35, 1);
				SOUNDMANAGER->play("����������ȵǿ�", 1.0f);
			}
		}

		// �ζ� �������
		if (SOUNDMANAGER->getLength("����������ȵǿ�") == SOUNDMANAGER->getPosition("����������ȵǿ�"))
		{
			if (!_diaSound[23])
			{
				_diaSound.set(23, 1);
				SOUNDMANAGER->play("�ζ�������", 1.0f);
			}
		}

		// ���� �������༮��
		if (SOUNDMANAGER->getLength("�ζ�������") == SOUNDMANAGER->getPosition("�ζ�������"))
		{
			if (!_diaSound[24])
			{
				_diaSound.set(24, 1);
				SOUNDMANAGER->play("�����������༮��", 1.0f);
			}
		}

		// �ζ� �������ҿ�
		if (SOUNDMANAGER->getLength("�����������༮��") == SOUNDMANAGER->getPosition("�����������༮��"))
		{
			if (!_diaSound[25])
			{
				_diaSound.set(25, 1);
				SOUNDMANAGER->play("�ζ������ҿ�", 1.0f);
			}
		}

		// ���� �������
		if (SOUNDMANAGER->getLength("�ζ������ҿ�") == SOUNDMANAGER->getPosition("�ζ������ҿ�"))
		{
			if (!_diaSound[26])
			{
				_diaSound.set(26, 1);
				SOUNDMANAGER->play("����������", 1.0f);
			}
		}

		// �ζ� �׷�����
		if (SOUNDMANAGER->getLength("����������") == SOUNDMANAGER->getPosition("����������"))
		{
			if (!_diaSound[27])
			{
				_diaSound.set(27, 1);
				SOUNDMANAGER->play("�ζ�׷�����", 1.0f);
			}

		}

		// ���� �ζ��ڵ�
		if (SOUNDMANAGER->getLength("�ζ�׷�����") == SOUNDMANAGER->getPosition("�ζ�׷�����"))
		{
			if (!_diaSound[28])
			{
				_diaSound.set(28, 1);
				SOUNDMANAGER->play("����ζ��ڵ�", 1.0f);
			}
		}

		// �ζ� �ȳ�
		if (SOUNDMANAGER->getLength("����ζ��ڵ�") == SOUNDMANAGER->getPosition("����ζ��ڵ�"))
		{
			IMAGEMANAGER->findImage("�ζ󴫰���")->render(getMemDC());

			if (!_diaSound[29])
			{
				_diaSound.set(29, 1);
				SOUNDMANAGER->play("�ζ�ȳ�", 1.0f);
			}
		}


		IMAGEMANAGER->findImage("�Ͼ����")->alphaRender(getMemDC(), _bigImageAlpha);

		// ��
		if (_bigImageAlpha==255)
		{
			_diaCount++;
			_BGalpha = 0;
			_tick = 0;
			_bigImageAlpha = 255;
		}

	}

#pragma endregion

#pragma region 2�� ������ ������ �ó�����

// ��� 17��
// ���� 31��
// 2�� ���� ������ ��������
// ����Ʈ - �ٳ����˳�?
	else if (_diaCount == 18)
	{
		if (!_diaSound[34])
		{
			SOUNDMANAGER->stopAllSound();
			_diaSound.set(34, 1);
			SOUNDMANAGER->play("dia18�����", 0.2f);
		}
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;

			_bigImageAlpha2 += 5;
			if (_bigImageAlpha2 >=255)_bigImageAlpha2 = 255;
		}

		if (SOUNDMANAGER->getLength("����Ʈ�ٳ����˳�") == SOUNDMANAGER->getPosition("����Ʈ�ٳ����˳�"))
		{
			_bigImageAlpha2 -= 5;
			if (_bigImageAlpha2 <= 0)_bigImageAlpha2 = 0;
		}

		IMAGEMANAGER->findImage("�Ͼ����")->alphaRender(getMemDC(), _bigImageAlpha);

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha2);

		//���̾�α� ����
		if (!_diaSound[31])
		{
			_diaSound.set(31, 1);
			SOUNDMANAGER->play("����Ʈ�ٳ����˳�", 1.0f);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(17, 120, 590, 1000, 500, 25, 255, 255, 255);

		
		if (_bigImageAlpha2 == 0)
		{
			_bigImageAlpha2 = 0;
			_bigImageAlpha = 0;
			_tick = 0;
			_diaCount++;
		}
	}

// ���� - �ҽ����ΰ�
	else if (_diaCount == 19)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("���򺹼��ɿ�") == SOUNDMANAGER->getPosition("���򺹼��ɿ�"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <=0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150, 200, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[32])
		{
			SOUNDMANAGER->play("���򺹼��ɿ�", 1.0f);
			_diaSound.set(32, 1);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(18, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}

	else if (_diaCount == 20)
	{
		// ĳ���� ���� ����
		if (_tick < 200)
		{
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("����Ʈ�����ض�") == SOUNDMANAGER->getPosition("����Ʈ�����ض�"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
		}

		// ĳ���� �̹���
		IMAGEMANAGER->findImage("����Ʈ")->alphaRender(getMemDC(), 350, 250, _bigImageAlpha);

		//���̾�α� ����
		if (!_diaSound[33])
		{
			SOUNDMANAGER->play("����Ʈ�����ض�", 1.0f);
			_diaSound.set(33, 1);
		}

		// ���̾�α� â
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), 100, 580, 215);
		// ���̾�α� �ؽ�Ʈ
		_dia->drawTextNoSkip(19, 120, 590, 500, 500, 25, 255, 255, 255);

		if (_bigImageAlpha == 0)
		{
			_bigImageAlpha = 0;
			_diaCount++;
			_tick = 0;
		}
	}
	else if (_diaCount == 21)
	{
		_lastAlpha -= 5;
		if (_lastAlpha <= 0)
		{
			_lastAlpha = 0;
			SCENEMANAGER->changScene("�ε�","����");
		}
	}
	else if (_diaCount==22)
	{
	IMAGEMANAGER->findImage("��������")->render(getMemDC());
	SCENEMANAGER->changScene("�ε�", "����");
	}

#pragma endregion

}

