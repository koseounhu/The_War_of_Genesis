#include "Stdafx.h"
#include "Dragon.h"
#include "Player.h"
#include "Enemy2.h"

HRESULT Dragon::init(void)
{
	// ����
	_phase = 0;

	// ��üƽ
	_tick = 0;


	// ���۱�
	_frame = 0;
	
	//������ ����
	_endSound = 1.0f;
	return S_OK;
}

void Dragon::release(void)
{

}

void Dragon::update(void)
{
	// ��ų ����� ������ pl, em �������ְ� ����Ұ�!!



	// ��üƽ
	_tick++;


	

	// ��ų��
	if (_phase == 0)
	{
	 	if (!SOUNDMANAGER->isPlaySound("�������"))
	 		SOUNDMANAGER->play("�������", 1.0f);

		if (_tick % 8 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("��ų��")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
				for (int i = 0; i < _em.size(); i++)
				{
					_moveDragon.push_back(_em[i].y);
				}

			}
		}
	}

	// �巡��
	else if (_phase == 1)
	{
		if (!SOUNDMANAGER->isPlaySound("����巡��"))
			SOUNDMANAGER->play("����巡��", 1.0f);


		if (_tick % 12 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("�巡��")->getMaxFrameX())
			{
				_moveDragon.clear();
				_frame = 0;
				_phase++;
			}
		}
	}

	// ����
	else if (_phase == 2)
	{
		if (!SOUNDMANAGER->isPlaySound("���泫��"))
			SOUNDMANAGER->play("���泫��", 1.0f);


		if (_tick % 5 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("��Ż����")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
			}
		}
	}

	// ��������
	else if (_phase == 3)
	{
		if (!SOUNDMANAGER->isPlaySound("��������"))
			SOUNDMANAGER->play("��������", 1.0f);
		
		if (_tick % 5 == 0)
		{
			
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("��������")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
			}
		}

	}
	else
	{
		// ��ų�� ����� ��� ���� �ʱ�ȭ
		_tick = 0;
		_frame = 0;
		_phase = 0;
	}
}

void Dragon::render(void)
{
	// ��ų��
	if (_phase == 0)
	{
		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl.x-110, _pl.y-100, 80, _frame, 0);
	}

	// �巡��
	else if (_phase == 1)
	{
		for (int i = 0; i < _moveDragon.size(); i++)
		{
			IMAGEMANAGER->findImage("�巡��")->alphaFrameRender(getMemDC(), _em[i].x-100, _moveDragon[i]-100, 205, _frame, 0);
			_moveDragon[i] -= 3;
		}
	}

	// ����
	else if (_phase == 2)
	{
		for (int i = 0; i < _em.size(); i++)
		{
			IMAGEMANAGER->findImage("��Ż����")->alphaFrameRender(getMemDC(), _em[i].x-90, _em[i].y-400, 120, _frame, 0);
			IMAGEMANAGER->findImage("��Ż��������")->alphaFrameRender(getMemDC(), _em[i].x-90, _em[i].y-400, 120, _frame, 0);
		}
	}

	// ��������
	else if (_phase == 3)
	{
		for (int i = 0; i < _em.size(); i++)
		{
			IMAGEMANAGER->findImage("����â")->alphaFrameRender(getMemDC(), _em[i].x-50 , _em[i].y-150 , 55, _frame, 0);
			IMAGEMANAGER->findImage("����â����")->alphaFrameRender(getMemDC(), _em[i].x-50 , _em[i].y-150, 255, _frame, 0);

			IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _em[i].x-110 , _em[i].y-140 , 150, _frame, 0);
			IMAGEMANAGER->findImage("�������߱���")->alphaFrameRender(getMemDC(), _em[i].x - 110, _em[i].y-140, 255, _frame, 0);
		}
	}







}
