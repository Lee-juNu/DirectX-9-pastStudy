// stdafx.h : 미리 컴파일된 헤더파일 : 자주 사용하는 것들을 미리 정의해 두는 곳
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <Ole2.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "d3dUtility.h"


//원래 이렇게 윗부분에다가 쓰면 안된다는데 쓰레드 안사용하고 std이름 겹치는게 아직 없어서 사용중
//나중에 겹치면 뺄 생각
using namespace std;

//=======================================================
// ## 윈도우 설정 디파인 ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("DIRECT3D Game")
#define WINSTARTX	0			//윈도우 시작좌표 X
#define WINSTARTY	0			//윈도우 시작좌표 Y
#define WINSIZEX	800		//윈도우 가로크기
#define WINSIZEY	800		//윈도우 세로크기
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}


//다른 CPP로 넘어갈 수 있게해주는 extern 
extern HINSTANCE	_hInstance;		//인스턴스 핸들
extern HWND			_hWnd;			//핸들
extern POINT		_ptMouse;

extern IDirect3DDevice9* Device;
