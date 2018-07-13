#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class page3 : public gameNode
{
private:
#define MAXBOX 36
#define	MAXBOXLX 3
#define MAXBOXLY 6
#define	MAXBOXRX 6
#define MAXBOXRY 3

private:
	image * _titleImage[2];
	tagBox _box[MAXBOX];

	POINT	_center;

public:
	page3();
	~page3();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);			// 박스 초기화

	void checkBox(void);		// 박스 체크시 상태 변경

	void titleRender(void);		// 타이틀 폰트 렌더
	void tileRender(void);		// 타일 이미지 렌더
	void boxRender(void);		// 박스 이미지 렌더

	void setIndex(int index);
	void setCenterPoint(POINT point);

	void setBox(int index, int startX, int startY, int endX, int endY, AUTOCHECK autoCheck, TERRAIN terrain);
};