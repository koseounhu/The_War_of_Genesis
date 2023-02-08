#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_dia = new Dialogue;
	_dia->init(1);

	// ��ü ƽ
	_tick = 0;

	// ���� ��� ����
	_BGalpha = 0;

	// ���̾�α� ī��Ʈ
	_diaCount = 15;

	// ū�̹���
	_bigImageAlpha2 = _bigImageAlpha = 0;

	// ���̾�α� ���� �ʱ�ȭ
	_diaSound.reset();

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


	_dia->update();
}


void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("�ƽŹ��")->alphaRender(getMemDC(), _BGalpha);

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
		else if (SOUNDMANAGER->getLength("�ζ��ڻ�") == SOUNDMANAGER->getPosition("�ζ��ڻ�"))
		{
			_bigImageAlpha -= 10;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
			
			if (!_diaSound[15])
			{
				_diaSound.set(15, 1);
				SOUNDMANAGER->play("����ȵ�", 1.0f);
			}
		}

		// ĳ���� �̹���
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
		_dia->drawTextNoSkip(_diaCount, 120, 590, 800, 500, 25, 255, 255, 255);


		// �ӽ�
		if (SOUNDMANAGER->getLength("�ζ��ڻ�") == SOUNDMANAGER->getPosition("�ζ��ڻ�"))
		{
			_bigImageAlpha = 0;
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
			_bigImageAlpha += 5;
			if (_bigImageAlpha >= 255)_bigImageAlpha = 255;
		}
		if (SOUNDMANAGER->getLength("����Ʈ����") == SOUNDMANAGER->getPosition("����Ʈ����"))
		{
			_bigImageAlpha -= 5;
			if (_bigImageAlpha <= 0)_bigImageAlpha = 0;
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





}

