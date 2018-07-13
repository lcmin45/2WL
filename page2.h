#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page2 : public gameNode
{
private:
#define MAXBOX 18
#define	MAXBOXX 3
#define MAXBOXY 3

private:
	image * _titleImage[2];
	tagBox	_box[MAXBOX];

	POINT	_center;

public:
	page2();
	~page2();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);			// 박스 초기화

	void titleRender(void);		// 타이틀 폰트 렌더
	void tileRender(void);		// 타일 이미지 렌더
	void boxRender(void);		// 박스 이미지 렌더

	void checkBox(void);		// 박스 체크시 상태 변경

	void setIndex(int index);	// 인덱스 설정
	void setCenterPoint(POINT point);

};
