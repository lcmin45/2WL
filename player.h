#pragma once
#include "gameNode.h"
#include "skill.h"
#include "inventory.h"

#define SPEED 5.0f

enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //방향
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2, DASH }; //행동
enum ANGLE { ANGLE0, ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5, ANGLE6, ANGLE7 }; //각도 (라디안 기준 0부터 2PI까지 8분할)

class projectileManager;

class player : public gameNode
{
private:
	POINTFLOAT _position; //좌표
	DIRECTION _direction; //방향
	ACTION _action; //행동
	ANGLE _angle; //각도
	image* _image; //이미지
	animation* _animation; //에니매이션
	RECT _body; //바디
	float _speed; //스피드
	float _dashSpeed; //대쉬 스피드

	projectileManager* _ptM; // 투사체 매니저 호환

	//임시
	RECT _zOrderBox;
	RECT _box;
public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyProcess(); //키 입력 처리
	void attackAngleProcess(); //공격 각도 처리
	void animationProcess(); //에니매이션 처리
	void actionProcess(); //행동 처리
	static void afterAction(void* obj); //에니매이션 콜백용

	DIRECTION getDirection() { return _direction; }
	void setAction(ACTION action) { _action = action; }
	void setAnimation(animation* animation) { _animation = animation; }


	//=======================스킬 사용 =================
	POINTFLOAT getPosition() {return _position;}
	void setProjectileManagerAddressLink(projectileManager* getLink) { _ptM = getLink; }
};