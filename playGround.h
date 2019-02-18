#pragma once

class playGround
{
private:	
public:
	HRESULT init(void);		//초기화 함수
	void release(void);		//메모리 관련 해제
	void update(void);		//업데이트(연산)
	void render(void);		//그려주는 함수

	playGround();
	~playGround();
};

