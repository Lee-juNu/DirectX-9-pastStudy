#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}

playGround::~playGround()
{
}
																							//�̰� ����
																							//�ƹ��͵�����?
//�ʱ�ȭ
HRESULT playGround::init()
{
	return S_OK;
}
//�޸� ���� ����
void playGround::release(void)
{
}
//����
void playGround::update(void)
{

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
			D3DCOLOR_ARGB(255,0,0,0),			//���� ��� �Ұ��Ҷ� ������������?
			1.0f,								//���� ���ۿ� �����ϰ��� �ϴ� ��
			0);									//���ٽ� ���ۿ� �����ϰ��� �ϴ� ��
		
		//���۰�    ��������
		Device->BeginScene();
		//�� ���̿� �ڵ��Ͻÿ�
		Device->EndScene();
		//��        ���ް�

		Device->Present(0, 0, 0, 0); //�ĸ� ���۸� �ÿ��Ѵ�
	}
}

