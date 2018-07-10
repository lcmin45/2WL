#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "tileObject.h"
#include "miniMap.h"

class mapTile : public gameNode
{
private:
	struct tagAutoPoint
	{
		POINT	_startPoint;
		POINT	_endPoint;
	};

private:
	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];
	miniMap*			_miniMap;

	bool				_isMouseBook;		// ���콺�� å���� �ִ��� üũ
	tagAutoPoint		_autoPoint;
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

	void tileInit(void);			// ��ü Ÿ�� �ʱ�ȭ

	void inputKey(void);			// �Է� Ű ó��
	void checkTile(void);			// Ÿ�� üũ Ű ó��
	void checkTerrain(void);		// �ڽ��� ���� üũ
	void checkImageObject(void);	// �ڽ��� �̹��� ������Ʈ üũ
	void checkObject(void);			// �ڽ��� ������Ʈ üũ
	void checkAuto(void);			// �ڽ��� �ڵ�Ÿ�� üũ
	void checkRoomIndex(void);		// ���� ����� �ε��� ����
	void checkEraser(void);

	void terrainRender(void);		// ���� ����
	void imageObjectRender(void);	// �̹��� ������Ʈ ����
	void classObjectRender(void);	// ������Ʈ ����
	void tileBoxRender(void);		// Ÿ�� �ڽ� ����
	void pointRender(void);			// ��ǥ ����
	void mouseBoxRender(void);		// ���콺�� �ִ� �ڽ� ����
	void mousePointRender(void);	// ���콺 üũ ����

	void save(void);				// ����
	void load(void);				// �ҷ�����
	void minimap(void);				// �̴ϸ� �����ֱ�

	void setIsMouseBook(bool isMouseBook) { _isMouseBook = isMouseBook; }

	void setIsMiniMap(bool isCheck) { _isMiniMap = isCheck; }
	bool getIsMiniMap(void) { return _isMiniMap; }

	void setMiniMapMemoryAddressLink(miniMap* map) { _miniMap = map; }
};
