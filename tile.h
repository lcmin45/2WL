#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H 
	//F == �� �Ÿ� ��� (TotalCost)
	//G == ���������κ��� ���� ������ ��κ��(CostFromStart)
	//H == ������κ��� ���������� ��κ��(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//�����ִ� Ÿ������ ����

	tile* _parentNode; //���� ���� Ÿ�� (��� ���ŵǴ� Ÿ��)
	
	const char* _attribute;
public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }
	
	RECT getRect() { return _rc; }

	//============ ������ ���� ������ & ������ ===============
	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(const char* str) { _attribute = str; }
	const char* getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};
