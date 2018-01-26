#pragma once
#include "BulletBase.h"

class BulletNormal :public BulletBase {
public:
	BulletNormal();
	~BulletNormal();

	CREATE_FUNC(BulletNormal);
	virtual bool init();

	static BulletNormal*create(Sprite* sprite);
	bool init(Sprite* sprite);
protected:
	virtual void onLockAim(Entity *aim);
private:
	void moveEnd();
};