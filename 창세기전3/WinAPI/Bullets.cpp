#include "Stdafx.h"
#include "Bullets.h"

HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img)
	}

	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();
}

void MissileM1::render(void)
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	// 최대 발사 갯수를 막는다
	if (_bulletMax <= _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 4.0f;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());


	_vBullet.push_back(bullet);
}

void MissileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) // m1의 특성으로인해 증감연산자를 빼고 밑에 코드에서 추가해준다.
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// 사거리 밖으로 나갓다.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y + 100))
		{
			// 주의
			// 원본 -> 로켓 -> 렌더링 순이면 다시 순차적으로 내려와서 지워야한다.
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void MissileM1::removeBullet(int arrNum)
{

	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);




}

// ############################################################################################################################################

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;

		// ZeroMemory() :  첫번째 인자가 가르키는 주소값을 0으로 초기화
		//					ㄴ 인자 : 메모리블록, 메모리블록사이즈
		// ZeroMemory는 내부적으로 memset을 호출하고있다.
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = new GImage;
		bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f, 416 , 64 , 13 , 1, true, RGB(255, 0, 255));
		bullet.fire = false;
		bullet.speed = 5.0f;
		
		_vBullet.push_back(bullet);
	}



	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img)
	}

	_vBullet.clear();
}

void Missile::update(void)
{
	move();
}

void Missile::render(void)
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire)continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		break;
	}
}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire)continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}

}

void Missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// 사거리 밖으로 나갓다.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}

	}

}

//====================================================================================================

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void Beam::release(void)
{
	// 가독성을 위해 사용
	// 람다를 사용해서 함수를 제끼고 들어왔을때 초기식이없기때문에 실행되지않는 방법이다 표준이 아니기때문에
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	////////////// 협업을 한다면 이렇게 작성해야한다.
	////////////// 정확하게 무엇을 하는 역할인지 알려주고 이터레이터를 돌려야한다.
	//////////////iterBullet iterBullet = _vBullet.begin();
	//////////////for (; iterBullet != _Bullet.end(); ++_viBullet)
	//////////////{
	//////////////	SAFE_DELETE(_viBullet->img);
	//////////////}

	////////////// 4. 협업시 가장 하지 말아야할 코드 오토를 사용하면 어떤 건지 명확하게 파악이안된다.
	//////////////for (auto iterBullet = _vBullet.begin();; iterBullet != _Bullet.end(); ++_viBullet)
	//////////////{
	//////////////	SAFE_DELETE(_viBullet->img);
	//////////////}

	////////////// 5 . 업계에서 많이 사용하는 방식 
	////////////// 컨테이너 기반 포문 -> 간소화를 위해 사용 -> 남이 읽는 것을 생각하지않고 사용
	////////////for (auto iter : _vBullet)			// 시작점과 끝점이 정해져있지않기때문에 전부다 auto로 실시간으로 가져와서 삭제하겟다
	////////////{
	////////////	SAFE_DELETE(_viBullet->img);	// 동적메모리 힙영역에 들어가있다.
	////////////}

	////////////// 6. C++에서 쓰면 죄악이다 스마트포인터가 잇기때문에 사용하지않는다. 굉장히 무겁기떄문에 게임쪽에서 사용하지않는다.
	////////////// for each문 자체를 권장하지 않는다. 
	////////////for each (auto iter in _vBullet)	// 시작점과 끝점이 정해져있지않기때문에 전부다 auto로 실시간으로 가져와서 삭제하겟다
	////////////{
	////////////	SAFE_DELETE(iter.img);			// 정적메모리 스택영역에 들어가잇다.
	////////////}

	////////////// 7. 델리게이트와 람다에 특화된 기능 C++ 17에서 기능확장되었다.
	////////////// 반복자의 시작과 끝 / 그리고 함수를 파라미터로 받는다.
	////////////// for_each 와 transform을 가장 많이 물어본다.
	//////////////for_each(_vBullet.begin(), _vBullet.end(), update);
	//////////////{
	//////////////}

	////////////// 람다 수식
	////////////int Value = 0;
	////////////for_each(_vBullet.begin(), _vBullet.end(), [&Value](auto& number)
	////////////{
	////////////		Value += number;
	////////////});
	/////////////*
 ////////////    	[] () {} ()
	////////////- [캡처] (매개변수) {(반환) 함수동작} (호출인자(생략가능)
	////////////- 람다 사용시 불필요한 부분이 사라져서 코드 간결화를 얻을 수 있다. , 함수를 선언하지않고 간단한 함수기능을 사용하기위해
	////////////[] (int numA, int numB){cout << numA+numB<<endl;}(10,20)
	////////////[] (int numA, int numB){return numA + numB}(10,20) 17부터는 ;이 빠져서 리턴뒤에 붙지않는다
	////////////*/

	////////////int numberA = 10;
	////////////int numberB = 10;
	////////////auto resultA = [](int NumA, int NumB) {return NumA + NumB; }(10, 10);
	////////////auto resultB = [&]()->int {return numberA + numberB; }();				// & 캡처영역에 잇는 모든 변수 체크를 하겟다
	////////////auto resultC = [=, &numberA]()->int {return numberA + numberB; }();		// = 값으로 추출하겟다


	/////////////*
	////////////[] : 같은 영역에 있는 모든 변수에 접근불가
	////////////[&] : 같은 영역에 있는 모든 변수를 참조로 캡처
	////////////[=] : 같은 영역에 있는 모든 변수를 값으로 캡처
	////////////[=, &변수A] : 같은 영역에 있는 모든 변수를 값으로 캡처 / 단, 변수A만 참조
	////////////*/

	////////////// 8. 트랜스폼 물어본다면 선뜻 대답을 하지말고 엔진에서 사용하는 것인지 언어적으로 사용하는것인지 물어봐야한다.
	////////////// transform : 반복자를 이용한 반복문 (결과를 다른 컨테이너에 저장)
	//////////////		ㄴ 원본도 가능
	////////////vector<int> vBulletReload;
	////////////// 원본 수식
	////////////// 람다를 많이 사용해야한다.
	////////////transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(),update); // 불렛의 시작부터 끝까지 반복을 돌고 업데이트하면서  불렛리로드를 넣어주겟다
	////////////// 트랜스폼 + 람다
	////////////transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(),
	////////////	[](__int64 numA)->auto{return numA; });

	_vBullet.clear();


}

void Beam::update(void)
{
	move();
}

void Beam::render(void)
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Object/beam.bmp", 0.0f, 0.0f, 412, 801, 4, 1, true, RGB(255, 0, 255));
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 0.1f;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());


	_vBullet.push_back(bullet);
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) // m1의 특성으로인해 증감연산자를 빼고 밑에 코드에서 추가해준다.
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// 사거리 밖으로 나갓다.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}


//===================================================================================================================================

HRESULT Bullet::init(const char* imagName, int bulletMax, float range)
{
	_imageName = imagName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	move();
}


void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());


	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) // m1의 특성으로인해 증감연산자를 빼고 밑에 코드에서 추가해준다.
	{
		_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)*_viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getWidth(), _viBullet->img->getHeight());

		// 사거리 밖으로 나갓다.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
