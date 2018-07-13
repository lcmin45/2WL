#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page1 : public gameNode
{
private:
#define MAXBOX 72
#define	MAXBOXX 6
#define MAXBOXY 6

private:
	image * _titleImage[2];
	tagBox	_box[MAXBOX];

	POINT	_center;

public:
	page1();
	~page1();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);					// 박스 초기화

	void checkBox(void);				// 박스 체크시 상태 변경

	void titleRender(void);				// 타이틀 폰트 렌더
	void tileRender(void);				// 타일 이미지 렌더
	void boxRender(void);				// 박스 형태 렌더

	void setIndex(int index);			// 인덱스 설정
	void setCenterPoint(POINT point);

	void setBox(int index, int frameX, int frameY);	// 박스 초기화를 쉽게 하기 위해 만든 함수
};


