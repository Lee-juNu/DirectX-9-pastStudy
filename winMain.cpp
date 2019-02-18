#include "stdafx.h"
#include "playGround.h"

//API :: Application Programming Interface

//=======================================================
//					##  전역변수 ##
//=======================================================
HINSTANCE	_hInstance;		//인스턴스 핸들
HWND		_hWnd;			//핸들

//마우스 좌표를... 가져와...
POINT _ptMouse;
//정적 바인딩
playGround _pg;

IDirect3DDevice9* Device = 0;


void setWindowSize(int x, int y, int width, int height);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	MSG			message;		//메시지 구조체


	//D3D와 윈도우클래스를 초기화(D3DUtility In 3DGameFrameWork)
	//인스턴스,사이즈x,사이즈y,창모드??,HAL,REF?,리턴당할 디바이스
	if (!d3d::InitD3D(hinstance,
		WINSIZEX, WINSIZEY, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	//준비가 끝났다 이제 여기 난잡해지기 싫으니
	//init->update->render->release의 순서대로 반복하는 곳을 만들어주자

	//플레이 그라운드 init
	if (FAILED(_pg.init()))
	{
		return 0;
	}

	while (true)
	{
		//메세지가 있으면 주워랏
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			
			TranslateMessage(&message);		//키보드 입력 시 그 메시지 처리 담당
			DispatchMessage(&message);		//실제로 윈도우에 메시지를 전달해주는 역할
		}
		else
		{
			_pg.update();
			_pg.render();
		}
	}
	_pg.release();

	Device->Release();

	return 0;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//퇴근 신호오면 파괴!
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

			//ESC보면 퇴근이다
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				::DestroyWindow(hwnd);
			break;
			//마우스 좌표... 가져와...
		case WM_MOUSEMOVE:
		{
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		}
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//윈도우 사이즈 재조정을 해준다
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//윈도우 위치를 재조정
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}


