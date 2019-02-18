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
	//������ ���ø����̼� ����
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

	//����ü ���
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

	//Direct3D�� �ʱ�ȭ�Ѵ�

	//���� �ߴ��� �˷��ִ� �����Դϴ�
	HRESULT hr = 0;

	// Step 1: IDirect3d�� �����.


	//Direct3DCreate9�� �������ڴ� �׻� D3D_SDK_VERSION�� �����ؾ��Ѵ�.
	//�� ���ڴ� ���ø����̼��� �ùٸ� ������Ϸ� ����������� Ȯ���ϱ� ����
	//���н� null�����͸� �����Ѵ�.
	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	//���� ���Ѱ�ó�� �ùٸ� ��������� �ƴϸ� null�� ����
    if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: �ϵ���� ���ؽ� ���μ��� Ȯ��.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(
		D3DADAPTER_DEFAULT,//Ư���� ����� �ϴ� ���� ���÷��� ����͸� �����Ѵ�.
		deviceType, //�̿��� ��ġ Ÿ���� �����Ѵ� 
		&caps);//�ּҸ� ������ ����?? �ʱ�ȭ�� Ư�� ����ü ����

	//�ϵ���� ���ؽ� ���μ����� �̿��� �� �ִ°�?
	int vp = 0;
	//������ �ϵ���� ���ؽ� ���μ������� �ž��ϰ� ��������
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	//�̷� ���ϴ� �����̶�� CPUȤ���Ű��
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	

	// Step 3:D3DPRESENT_PARAMETERS ����ü ä���

	//WinAPI�� �ϴ� winŬ���� ä���� ����ѵ�
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;	//�ȼ� ������ �ĸ� ���� �ʺ�
	d3dpp.BackBufferHeight           = height;  //�ȼ� ������ �ĸ� ���� ����
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8; // �ĸ� ������ �ȼ� ����
	d3dpp.BackBufferCount            = 1;//�̿��� �ĸ� ������ �� ������ 1���� �ĸ� ����
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE; //�ĸ� ���ۿ� �̿��� ��Ƽ ���ø��� Ÿ��
	d3dpp.MultiSampleQuality         = 0;//��Ƽ ���ø��� ����
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; //�ø��� ü���� ���۰� ��ȯ�Ǵ� ����� �����ϴ� D3DSWAPEEFECT������ ���
	d3dpp.hDeviceWindow              = hwnd;//����� ������ �ڵ�, ������� ����� �� ���ø����̼� ������ ����
	d3dpp.Windowed                   = windowed;//������ ���� �����߸� ���� true�� ��üȭ���϶��� false�� �����Ѵ�
	d3dpp.EnableAutoDepthStencil     = true; //Direct3D�� �ڵ����� ����/���ٽ� ���۸� ����� �����ϱ� ���Ѵٸ� true
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8; //����/���ٽ� ������ ����
	d3dpp.Flags                      = 0;//�� ���� �ΰ����� Ư����. 0(�÷��� ����)�� �����ϰų� D3DPRESENTFLAG������ ����� �ϳ��� �����Ѵ�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //������� �����Ѵ�.
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT������ ���
	//IMMEDIATE��� �ÿ��Ѵ�.
	//DEFAULT ������ �ÿ� ������ Direct3D�� �����Ѵ�


	// Step 4: IDirect3DDevice9 �������̽� �����.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // ������� Direct3DDevice9 ��ü�� ������ ���� ���÷��� ����͸� �����Ѵ�.
		deviceType,         // �̿��� ��ġ Ÿ���� �����Ѵ� 
		hwnd,               // ��ġ�� ����� ������ �ڵ�
		vp,                 // ���ؽ� ���μ��� ������ ���ϰ����
	    &d3dpp,             // ��ġ Ư���� �Ϻθ� �����ϴ� �ʱ�ȭ�� D3DPRESENT_PARAMETERS�ν��Ͻ��� ����
	    device);            // ������ ����̽��� ����

	if( FAILED(hr) )
	{
		//���� ���������� ���������� 16��Ʈ�� �����ϰ� �ٽ� �õ��Ѵ�
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		//�׷��� �ȵǸ� ����̴� �޾Ƶ帮��
		if( FAILED(hr) )
		{
			d3d9->Release(); // ����̾� �޾Ƶ帮�� �����ص��
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	//����� d3d9�� ����
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


