#pragma once
#include "gameNode.h"

class ending : public gameNode
{
	int _index; //이미지 인덱스
	image* _image; //엔딩 이미지
	int _count; //인덱스 카운트
public:
	ending();
	~ending();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};