#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "tileObject.h"
#include "miniMap.h"

class mapTile : public gameNode
{
private:

private:
	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];
	miniMap*			_miniMap;

	bool				_isMouseBook;
	bool				_isCheck;
	POINT				_startPoint;
	POINT				_endPoint;

	bool				_isMiniMap;

public:
	mapTile();
	~mapTile();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void tileInit(void);			// 전체 타일 초기화

	void inputKey(void);			// 입력 키 처리
	void checkTile(void);			// 타일 체크 키 처리
	void checkTerrain(void);		// 박스에 지형 체크
	void checkObject(void);			// 박스에 오브젝트 체크
	void checkAuto(void);			// 박스에 자동타일 체크

	void terrainRender(void);		// 지형 렌더
	void objectRender(void);		// 오브젝트 렌더
	void tileBoxRender(void);		// 타일 박스 렌더
	void pointRender(void);			// 좌표 렌더
	void mouseBoxRender(void);		// 마우스가 있는 박스 렌더
	void mousePointRender(void);	// 마우스 체크 렌더

	void save(void);				// 저장
	void load(void);				// 불러오기
	void minimap(void);				// 미니맵 보여주기

	void setIsMouseBook(bool isMouseBook) { _isMouseBook = isMouseBook; }

	void setIsMiniMap(bool isCheck) { _isMiniMap = isCheck; }
	bool getIsMiniMap(void) { return _isMiniMap; }

	void setMiniMapMemoryAddressLink(miniMap* map) { _miniMap = map; }
};