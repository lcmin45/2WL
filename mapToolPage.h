#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

#define BOOK
 
class mapToolPage : public gameNode
{
private:
	struct tagTitle
	{
		image* img;
	};

	struct tagIcon
	{
		image*	img;
		image*	edgeImg;
		RECT	rc;
		POINT	center;
		int		frameX;
		int		frameY;
	};

private:
	int		_pageIndex;
	POINT	_center;

	tagTitle	_title[6];
	tagIcon	_box[36];
public:
	mapToolPage();
	~mapToolPage();

	virtual HRESULT init(int index);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);
	void checkPage(int index);


	void checkCenter(POINT bookCenter);
};

