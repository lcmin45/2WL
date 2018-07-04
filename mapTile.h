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

	void tileInit(void);			// ��ü Ÿ�� �ʱ�ȭ

	void inputKey(void);			// �Է� Ű ó��
	void checkTile(void);			// Ÿ�� üũ Ű ó��
	void checkTerrain(void);		// �ڽ��� ���� üũ
	void checkObject(void);			// �ڽ��� ������Ʈ üũ
	void checkAuto(void);			// �ڽ��� �ڵ�Ÿ�� üũ

	void terrainRender(void);		// ���� ����
	void objectRender(void);		// ������Ʈ ����
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