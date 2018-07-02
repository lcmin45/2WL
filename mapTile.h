#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "mapToolNode.h"
#include "tileObject.h"

class mapTile : public gameNode
{
private:
	
private:
	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];

	bool				_isMouseBook;
	bool				_isCheck;
	POINT				_startPoint;
	POINT				_endPoint;

public:
	mapTile();
	~mapTile();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);			// �̹��� �ʱ�ȭ
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

	void save(void);
	void load(void);
	void minimap(void);

	void setIsMouseBook(bool isMouseBook) { _isMouseBook = isMouseBook; }
};

