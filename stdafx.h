// stdafx.h : �̸� �����ϵ� ������� : ���� ����ϴ� �͵��� �̸� ������ �δ� ��
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <Ole2.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "d3dUtility.h"


//���� �̷��� ���κп��ٰ� ���� �ȵȴٴµ� ������ �Ȼ���ϰ� std�̸� ��ġ�°� ���� ��� �����
//���߿� ��ġ�� �� ����
using namespace std;

//=======================================================
// ## ������ ���� ������ ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("DIRECT3D Game")
#define WINSTARTX	0			//������ ������ǥ X
#define WINSTARTY	0			//������ ������ǥ Y
#define WINSIZEX	800		//������ ����ũ��
#define WINSIZEY	800		//������ ����ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}


//�ٸ� CPP�� �Ѿ �� �ְ����ִ� extern 
extern HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
extern HWND			_hWnd;			//�ڵ�
extern POINT		_ptMouse;

extern IDirect3DDevice9* Device;
