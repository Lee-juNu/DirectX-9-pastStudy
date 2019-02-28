#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}

playGround::~playGround()
{
}
																		
//초기화
HRESULT playGround::init()
{

	//삼각형 초기화
	tri.init();

	//프로젝션뷰 설정
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5,
		(float)WINSIZEX/ (float)WINSIZEY,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	
	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD); //강제로 32비트로 색상으로 바꿔서 사용하는 열거형 사용하지 않는다함

	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);	   //버텍스 점만 찍는 열거형  (주의.잘안보임)
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		   //안에 색상으로 채우는 상태의 열거형
	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);   //선으로 이어주는 열거형

	return S_OK;
}
//메모리 관련 삭제
void playGround::release(void)
{
	tri.release();
}
//연산
void playGround::update(void)
{
	tri.update();
}



//그리는거.......
void playGround::render(void)
{
	if (Device)
	{
		Device->Clear(0,//↓pRects 배열 내 사각형의 수 
			0,			//내가 pRects 소거하려는 화면 사각형의 배열. 
					    //표면의 특정 영역만 소거할 수 있도록 해준다.
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, //어떤 표면을 소거할지를 지정한다. 
												//여긴 (Target)후면,(ZBuffer)깊이버퍼
			D3DCOLOR_ARGB(255,255,255,255),			//렌더 대상 소거할때 무슨색상으로?
			1.0f,								//깊이 버퍼에 지정하고자 하는 값
			0);									//스텐실 버퍼에 지정하고자 하는 값
		
		//시작과    알파이자
		Device->BeginScene();



		tri.render();
		//이 사이에 코딩하시오



		Device->EndScene();
		//끝        오메가

		Device->Present(0, 0, 0, 0); //후면 버퍼를 시연한다
	}
}

