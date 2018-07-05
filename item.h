#pragma once
#include "gameNode.h"

enum TYPE { NONE, HP, DAMAGE, SPEED, CRITICAL, COIN };
enum STATUS { NOWHERE, ON_FIELD, IN_INVENTORY, IN_STORE };

struct EFFECT
{
	TYPE type; //아이템 효과
	int amount; //효과의 수치
};

class item : public gameNode
{
private:
	POINTFLOAT _position; //좌표
	STATUS _status; //현재 어디에 있는지
	EFFECT _effect[2]; //각 아이템 당 가진 효과는 2개
	image* _image; //이미지
	const char* _name; //이름
	const char* _info; //설명
	float _speed; //코인용 스피드
	animation* _animation; //코인용 애니메이션
public:
	item();
	~item();

	virtual HRESULT init(POINTFLOAT position, STATUS status, EFFECT effect0, EFFECT effect1, const char* imageName, const char* name, const char* info);
	virtual void release();
	virtual void update();
	virtual void render();
	void coinMove(float angle); //코인용 움직임 함수

	POINTFLOAT getPosition() { return _position; }
	STATUS getStatus() { return _status; }
	EFFECT* getEffect() { return _effect; }
	image* getImage() { return _image; }
	const char* getName() { return _name; }
	const char* getInfo() { return _info; }
	void setPosition(POINTFLOAT position) { _position = position; }
	void setStatus(STATUS status) { _status = status; }
};