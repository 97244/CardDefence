#pragma once
#include "BulletNormal.h"
#include "BulletBase.h"

#define BULLET_MAX_CACHE_NUM 10

class BulletBase;
class BulletManager :public Node {
public:
	BulletManager();
	~BulletManager();
	static BulletManager*create();
	bool init();

	BulletBase*getAnyUnUsedBullet();
private:
	Vector<BulletBase*>m_bulletList;
	void createBullets();
	void bulletLogicCheck(float dt);
};