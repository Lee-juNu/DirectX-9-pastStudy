#pragma once
#include "triangle.h"
class playGround
{
private:	
	triangle tri;
public:
	HRESULT init(void);		//�ʱ�ȭ �Լ�
	void release(void);		//�޸� ���� ����
	void update(void);		//������Ʈ(����)
	void render(void);		//�׷��ִ� �Լ�

	playGround();
	~playGround();
};

