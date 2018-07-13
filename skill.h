#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class 얼음던지기;
class 얼음던지기매니저;

enum SUBJECT
{
	PLAYER, ENEMY
};

struct PARTICLE
{
	image* img;						//파티클 이미지
	POINTFLOAT pt;					//파티클 좌표
	RECT rc;						//파티클 렉트
	int indexX;						//파티클 프레임 인덱스 X
	int indexY;						//파티클 프레임 인덱스 Y
	float angle;					//파티클 앵글
	float startTime;				//파티클 생성된시간 
};

class skill : public gameNode
{
protected:
	struct WOODPARTICLE
	{
		image* img;						//우드보스 파티클 이미지
		POINTFLOAT pt;					//우드보스 파티클 좌표
		RECT rc;						//우드보스 렉트
		int frameIndex;					//우드보스 프레임 인덱스
	};
	struct METEOR
	{
		image* img;						//파이어 보스 마법진 이미지 & 폭발 이미지
		image* img2;					//파이어 보스 메테오 이미지
		POINTFLOAT pt, pt2;				//파이어 보스 마법진 좌표,메테오 이미지
		RECT rc, rc2;					//파이어 보스 마법진 렉트,메테오 렉트
		int frameIndex, frameIndex2;	//파이어 보스 마법진 프레임인덱스, 메테오 프레임인덱스
		float startTime;				//파이어 보스 메테오 생성시간
	};
	struct collision
	{
		image* img;						
		POINTFLOAT ptStart;
		POINTFLOAT pt;
		RECT rc;
		int frameIndex;
	};
	tagMapToolTile* _tile;
	

protected:

	#define MAXPARTICLE 5

	SUBJECT _subject;
	image* _img;
	RECT _rc;
	char _str[1024];
	POINTFLOAT _firePt;
	POINTFLOAT _pt;
	float _angle;
	float _speed;
	float _range;
	float _damage;
	float _coolTime;
	int _amount;
	int _frameIndex;
	float _startTime;
	vector<WOODPARTICLE*>			vWood;
	vector<WOODPARTICLE*>::iterator	viWood;
	vector<METEOR*>				vMeteor;
	vector<METEOR*>::iterator	viMeteor;
	vector<얼음던지기*>			vIceThrow;
	vector<얼음던지기*>::iterator viIceThrow;
	vector<collision*>				vHail;
	vector<collision*>::iterator	viHail;


	RECT sRect[MAXPARTICLE];
public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//skillName : 1skill(불꽃타격, 바람베기, 흙주먹) 2skill(화염구, 맹렬회오리, 대지의방패),3skill(불타는올가미,사이클론부메랑,대지의고리)
	//개수, 시작좌표, 각도, 스피드, 사거리, 데미지
	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	//스킬 움직임
	virtual void move();

	//프레임 이미지
	virtual void frameCount();

	//충돌 판정용 사각형
	RECT getRect() { return _rc; }
	RECT* getsRect() { return sRect; }
	SUBJECT getSubject() { return _subject; }
	float getSkillDamage() { return _damage; }
	float getSkillAngle() { return _angle; }

	image* getImage() { return _img; }
	int getFrameIndex() { return _frameIndex; }


	vector<WOODPARTICLE*> getVWoodSkill() { return vWood; }
	vector<METEOR*>	getVMeteor() { return vMeteor; };
	vector<얼음던지기*>	getVIceThrow() { return vIceThrow; }
	vector<collision*>	getVHail() { return vHail; }
	void setTileAddressLink(tagMapToolTile* getLink) { _tile = getLink; }
};