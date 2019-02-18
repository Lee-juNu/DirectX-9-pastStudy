//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: d3dUtility.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Provides utility functions for simplifying common tasks.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "d3dUtility.h"


bool d3d::InitD3D(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	//윈도우 어플리케이션 생성
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)d3d::WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	//구조체 등록
	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	HWND hwnd = 0;
	hwnd = ::CreateWindow("Direct3D9App", "Direct3D9App", 
		WS_EX_TOPMOST,
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/); 

	if( !hwnd )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	//Direct3D를 초기화한다

	//실패 했는지 알려주는 아이입니다
	HRESULT hr = 0;

	// Step 1: IDirect3d를 만든다.


	//Direct3DCreate9의 단일인자는 항상 D3D_SDK_VERSION을 전달해야한다.
	//이 인자는 애플리케이션이 올바른 헤더파일로 만들어진것을 확인하기 위함
	//실패시 null포인터를 리턴한다.
	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	//위에 말한것처럼 올바른 헤더파일이 아니면 null값 리턴
    if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: 하드웨어 버텍스 프로세싱 확인.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(
		D3DADAPTER_DEFAULT,//특성을 얻고자 하는 물리 디스플레이 어댑터를 지정한다.
		deviceType, //이용할 장치 타입을 지정한다 
		&caps);//주소를 넣은건 뭐다?? 초기화된 특성 구조체 리턴

	//하드웨어 퍼텍스 프로세싱을 이용할 수 있는가?
	int vp = 0;
	//있으면 하드웨어 버텍스 프로세싱으로 씽씽하게 돌려주자
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	//이런 못하는 똥컴이라니 CPU혹사시키자
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	

	// Step 3:D3DPRESENT_PARAMETERS 구조체 채우기

	//WinAPI배울떄 하던 win클래스 채우기랑 비슷한듯
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;	//픽셀 단위의 후면 버퍼 너비
	d3dpp.BackBufferHeight           = height;  //픽셀 단위의 후면 버퍼 높이
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8; // 후면 버퍼의 픽셀 포맷
	d3dpp.BackBufferCount            = 1;//이용할 후면 버퍼의 수 보통은 1개의 후면 버퍼
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE; //후면 버퍼에 이용할 멀티 샘플링의 타입
	d3dpp.MultiSampleQuality         = 0;//멀티 샘플링의 레벨
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; //플리핑 체인의 버퍼가 교환되는 방법을 지정하는 D3DSWAPEEFECT열거형 멤버
	d3dpp.hDeviceWindow              = hwnd;//연결된 윈도우 핸들, 드로잉의 대상이 될 애플리케이션 윈도우 지정
	d3dpp.Windowed                   = windowed;//윈도우 모드로 실행중리 때는 true를 전체화면일때는 false를 지정한다
	d3dpp.EnableAutoDepthStencil     = true; //Direct3D가 자동으로 깊이/스텐실 버퍼를 만들고 관리하길 원한다면 true
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8; //깊이/스텐실 버퍼의 포맷
	d3dpp.Flags                      = 0;//몇 가지 부가적인 특성들. 0(플래그 없음)을 지정하거나 D3DPRESENTFLAG집합의 멤버중 하나를 지정한다
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //재생율을 지정한다.
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT집합의 멤버
	//IMMEDIATE즉시 시연한다.
	//DEFAULT 적절한 시연 간격을 Direct3D가 결정한다


	// Step 4: IDirect3DDevice9 인터페이스 만들기.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // 만들어질 Direct3DDevice9 객체와 대응될 물리 디스플레이 어댑터를 지정한다.
		deviceType,         // 이용할 장치 타입을 지정한다 
		hwnd,               // 장치와 연결될 윈도우 핸들
		vp,                 // 버텍스 프로세싱 위에서 정하고왔지
	    &d3dpp,             // 장치 특성의 일부를 정의하는 초기화된 D3DPRESENT_PARAMETERS인스턴스를 지정
	    device);            // 생성된 디바이스를 리턴

	if( FAILED(hr) )
	{
		//만약 실패했으면 깊이포맷을 16비트로 지정하고 다시 시도한다
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		//그래도 안되면 운명이다 받아드리자
		if( FAILED(hr) )
		{
			d3d9->Release(); // 운명이야 받아드리고 해제해드려
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	//사용한 d3d9은 해제
	d3d9->Release(); // done with d3d9 object
	
	return true;
}


D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

D3DLIGHT9 d3d::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.5f;
	light.Phi          = 0.7f;

	return light;
}

D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}


