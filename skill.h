#pragma once
#include "gameNode.h"

class ����������;
class ����������Ŵ���;

enum SUBJECT
{
	PLAYER, ENEMY
};

struct PARTICLE
{
	image* img;
	POINTFLOAT pt;
	RECT rc;
	int indexX;
	int indexY;
	float angle;
	float startTime;
};

class skill : public gameNode
{
protected:
	struct WOODPARTICLE
	{
		image* img;
		POINTFLOAT pt;
		RECT rc;
		int frameIndex;
	};
	struct METEOR
	{
		image* img;
		image* img2;
		POINTFLOAT pt, pt2;
		RECT rc, rc2;
		int frameIndex, frameIndex2;
		float startTime;
	};
	struct collision
	{
		image* img;
		POINTFLOAT ptStart;
		POINTFLOAT pt;
		RECT rc;
		int frameIndex;
	};
	

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
	vector<����������*>			vIceThrow;
	vector<����������*>::iterator viIceThrow;
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

	//skillName : 1skill(�Ҳ�Ÿ��, �ٶ�����, ���ָ�) 2skill(ȭ����, �ͷ�ȸ����, �����ǹ���),3skill(��Ÿ�¿ð���,����Ŭ�кθ޶�,�����ǰ�)
	//����, ������ǥ, ����, ���ǵ�, ��Ÿ�, ������
	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	//��ų ������
	virtual void move();

	//������ �̹���
	virtual void frameCount();

	//�浹 ������ �簢��
	RECT getRect() { return _rc; }
	RECT* getsRect() { return sRect; }
	SUBJECT getSubject() { return _subject; }
	float getSkillDamage() { return _damage; }
	float getSkillAngle() { return _angle; }

	image* getImage() { return _img; }
	int getFrameIndex() { return _frameIndex; }


	vector<WOODPARTICLE*> getVWoodSkill() { return vWood; }
	vector<METEOR*>	getVMeteor() { return vMeteor; };
	vector<����������*>	getVIceThrow() { return vIceThrow; }
	vector<collision*>	getVHail() { return vHail; }
};