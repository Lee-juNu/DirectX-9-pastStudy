#include "stdafx.h"
#include "playGround.h"

//API :: Application Programming Interface

//=======================================================
//					##  �������� ##
//=======================================================
HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
HWND		_hWnd;			//�ڵ�

//���콺 ��ǥ��... ������...
POINT _ptMouse;
//���� ���ε�
playGround _pg;

IDirect3DDevice9* Device = 0;


void setWindowSize(int x, int y, int width, int height);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	MSG			message;		//�޽��� ����ü


	//D3D�� ������Ŭ������ �ʱ�ȭ(D3DUtility In 3DGameFrameWork)
	//�ν��Ͻ�,������x,������y,â���??,HAL,REF?,���ϴ��� ����̽�
	if (!d3d::InitD3D(hinstance,
		WINSIZEX, WINSIZEY, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	//�غ� ������ ���� ���� ���������� ������
	//init->update->render->release�� ������� �ݺ��ϴ� ���� ���������

	//�÷��� �׶��� init
	if (FAILED(_pg.init()))
	{
		return 0;
	}

	while (true)
	{
		//�޼����� ������ �ֿ���
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			
			TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
			DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
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
		//��� ��ȣ���� �ı�!
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

			//ESC���� ����̴�
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				::DestroyWindow(hwnd);
			break;
			//���콺 ��ǥ... ������...
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

	//������ ������ �������� ���ش�
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//������ ��ġ�� ������
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}


