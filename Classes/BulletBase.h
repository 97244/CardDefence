#pragma once
#include "Entity.h"

/* ×Óµ¯ËÙ¶È */
#define SPEED_DEFAULT 10
#define SPEED_NORMAL 5
class BulletBase : public Entity
{
public:
	BulletBase();
	~BulletBase();
	void lockAim(Entity * entity);
	Entity *getAim();
	bool isArrive();

	void setUsed(bool isUsed);
	bool isUsed();
protected:
	virtual void onLockAim(Entity *aim) = 0;
	bool m_isArrive;
private:
	bool m_isUsed;
	Entity* m_aim;
	CC_SYNTHESIZE(int, m_iAtkValue, iAtkValue);
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
};