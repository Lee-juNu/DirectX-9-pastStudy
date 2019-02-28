#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}

playGround::~playGround()
{
}
																		
//�ʱ�ȭ
HRESULT playGround::init()
{

	//�ﰢ�� �ʱ�ȭ
	tri.init();

	//�������Ǻ� ����
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5,
		(float)WINSIZEX/ (float)WINSIZEY,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	
	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD); //������ 32��Ʈ�� �������� �ٲ㼭 ����ϴ� ������ ������� �ʴ´���

	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);	   //���ؽ� ���� ��� ������  (����.�߾Ⱥ���)
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		   //�ȿ� �������� ä��� ������ ������
	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);   //������ �̾��ִ� ������

	return S_OK;
}
//�޸� ���� ����
void playGround::release(void)
{
	tri.release();
}
//����
void playGround::update(void)
{
	tri.update();
}



//�׸��°�.......
void playGround::render(void)
{
	if (Device)
	{
		Device->Clear(0,//��pRects �迭 �� �簢���� �� 
			0,			//���� pRects �Ұ��Ϸ��� ȭ�� �簢���� �迭. 
					    //ǥ���� Ư�� ������ �Ұ��� �� �ֵ��� ���ش�.
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, //� ǥ���� �Ұ������� �����Ѵ�. 
												//���� (Target)�ĸ�,(ZBuffer)���̹���
			D3DCOLOR_ARGB(255,255,255,255),			//���� ��� �Ұ��Ҷ� ������������?
			1.0f,								//���� ���ۿ� �����ϰ��� �ϴ� ��
			0);									//���ٽ� ���ۿ� �����ϰ��� �ϴ� ��
		
		//���۰�    ��������
		Device->BeginScene();



		tri.render();
		//�� ���̿� �ڵ��Ͻÿ�



		Device->EndScene();
		//��        ���ް�

		Device->Present(0, 0, 0, 0); //�ĸ� ���۸� �ÿ��Ѵ�
	}
}

