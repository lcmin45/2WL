#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class tile : public gameNode
{
private:
	int _idX;		//에이스타에서 받아온 인덱스 X
	int _idY;		//에이스타에서 받아온 인덱스 Y

	POINT _center;	//중심점
	RECT _rc;		//렉트

	//F = G + H 
	//F == 총 거리 비용 (TotalCost)
	//G == 시작점으로부터 현재 노드까지 경로비용(CostFromStart)
	//H == 현재노드로부터 도착점까지 경로비용(CostToGoal)

	float _totalCost;		//토탈비용
	float _costFromStart;	//스타트 지점부터 현재까지 비용
	float _costToGoal;		//도착점까지 비용

	bool _isOpen;			//갈수있는 타일인지 유무
	tile* _parentNode;		//제일 상위 타일 (계속 갱신되는 타일)
	const char* _attribute;	//타일 타입

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

	//============ 편리를 위한 접근자 & 설정자 ===============
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

