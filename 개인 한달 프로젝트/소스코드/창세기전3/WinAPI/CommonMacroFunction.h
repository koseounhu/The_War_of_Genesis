#pragma once

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	//C++이지만 C스타일에 맞춰 NULL을 적어주지만 가끔 모호함때문에 자료형 맞춰줄 필요 있음. 예를 들어 bool과 BOOL.
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}

//사각형 그리기 (렉탱글 함수 사용)
inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

// RECT 중심점 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y- height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형 그리기 ( 랙탱글 함수 사용) - 헤더파일 두 번 불러오기 안 하려고 정의
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, width, height);
}

//타원 그리기(일립스 함수 사용)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//타원 센터점 중심으로 그리기 (일립스 함수 사용)
inline void ElipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline RECT CollisionAreaResizing(RECT& rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2, rcDest.right - width / 2, rcDest.bottom - height / 2 };
	return rc;
}